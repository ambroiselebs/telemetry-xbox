#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

# include <windows.h>
# include <iostream>
# include "OutFile.hpp"
# include <ctime>
# include <chrono>
# include <iomanip>
# include <sstream>

typedef struct {
	WORD wButtons;
	BYTE bLeftTrigger;
	BYTE bRightTrigger;
	SHORT sThumbLX;
	SHORT sThumbLY;
	SHORT sThumbRX;
	SHORT sThumbRY;
} XINPUT_GAMEPAD;

typedef struct {
	DWORD dwPacketNumber;
	XINPUT_GAMEPAD Gamepad;
} XINPUT_STATE;

# define XINPUT_GAMEPAD_A 0x1000
# define XINPUT_GAMEPAD_B 0x2000
# define XINPUT_GAMEPAD_X 0x4000
# define XINPUT_GAMEPAD_Y 0x8000

typedef	DWORD (WINAPI *XInputGetStateFunc)(DWORD, XINPUT_STATE*);

class Controller
{
private:
	HMODULE				xinput;
	XInputGetStateFunc	XInputGetState;
	XINPUT_STATE		state;
	XINPUT_STATE		prev;

	bool				reading_entries;
	OutFile&			outfile_lt;
	OutFile&			outfile_rt;
public:
	Controller(OutFile& outfile_lt, OutFile& outfile_rt);
	~Controller();

	void	init_xinput();
	void	init_xinput_get_state();
	void	load_controller();

	void	loop();

	void	read_buttons();
	void	read_triggers();

	std::string	write_infos(std::string input, int percent) const;
};

#endif
