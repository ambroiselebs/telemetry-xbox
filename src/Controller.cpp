#include "Controller.hpp"

Controller::Controller(OutFile& outfile_lt, OutFile& outfile_rt) : reading_entries(false), outfile_lt(outfile_lt), outfile_rt(outfile_rt) {
	this->init_xinput();
	this->init_xinput_get_state();
	this->load_controller();
}
Controller::~Controller() {
	FreeLibrary(this->xinput);
}

void	Controller::init_xinput() {
	this->xinput = LoadLibraryA("xinput1_4.dll");
	if (!this->xinput)
		this->xinput = LoadLibraryA("xinput1_3.dll");
	if (!this->xinput) {
		std::cerr << "XInput DLL not found" << std::endl;
		exit(1);
	}
	std::cout << "DLL loaded" << std::endl;
}

void	Controller::init_xinput_get_state() {
	this->XInputGetState = reinterpret_cast<XInputGetStateFunc>(GetProcAddress(xinput, "XInputGetState"));
	if (!this->XInputGetState) {
		std::cerr << "Function XInputGetState not found" << std::endl;
		exit(1);
	}
	std::cout << "Function XInputGetState loaded" << std::endl;
}

void	Controller::load_controller() {
	for (int i = 0; i < 4; i++) {
		DWORD	res = XInputGetState(i, &state);
		std::cout << "Controller " << i << " : ";
		if (res == 0)
			std::cout << "Connected" << std::endl;
		else
			std::cout << "Not connected" << std::endl;
	}
	std::cout << "Reading controller entries" << std::endl;

	this->prev = {};
}

void	Controller::read_buttons() {
	WORD	b = this->state.Gamepad.wButtons;
	WORD	pb = this->prev.Gamepad.wButtons;

	if ((b & XINPUT_GAMEPAD_A) && (pb & XINPUT_GAMEPAD_A)) {
		if (this->reading_entries) {
			std::cout << "Stopping reading entries" << std::endl;
			this->reading_entries = false;
		} else {
			std::cout << "Starting reading entries" << std::endl;
			this->reading_entries = true;
		}
	}
	if ((b & XINPUT_GAMEPAD_Y))
		std::cout << "Y" << std::endl;
}

void	Controller::read_triggers() {
	BYTE	lt = this->state.Gamepad.bLeftTrigger;
	BYTE	rt = this->state.Gamepad.bRightTrigger;
	int		lt_percent = (lt * 100) / 255;
	int		rt_percent = (rt * 100) / 255;

	std::cout << "LT: " << lt_percent << "%" << std::endl;
	this->outfile_lt.write_line(this->write_infos("LT", lt_percent));

	std::cout << "RT: " << rt_percent << "%" << std::endl;
	this->outfile_rt.write_line(this->write_infos("RT", rt_percent));
}

void	Controller::loop() {
	while (true) {
		DWORD	res = XInputGetState(0, &this->state);
		if (res == 0) {
			this->read_buttons();

			if (this->reading_entries)
				this->read_triggers();

			this->prev = this->state;
		}
		Sleep(100);
	}
}

std::string	Controller::write_infos(std::string input, int percent) const {
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		now.time_since_epoch()) % 1000;

	std::time_t	time = std::chrono::system_clock::to_time_t(now);
	std::tm*	t = std::localtime(&time);

	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(2) << t->tm_hour << "-"
		<< std::setfill('0') << std::setw(2) << t->tm_min << "-"
		<< std::setfill('0') << std::setw(2) << t->tm_sec << "-"
		<< std::setfill('0') << std::setw(3) << ms.count() << ","
		<< percent << "," << input;

	return oss.str();
}
