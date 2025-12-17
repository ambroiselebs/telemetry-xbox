#include <iostream>
#include "Controller.hpp"
#include "GraphLoader.hpp"

void	record_entries(std::string file_brake, std::string file_throttle) {
	OutFile		outfile_lt(file_brake);
	OutFile		outfile_rt(file_throttle);
	Controller	controller(outfile_lt, outfile_rt);

	controller.loop();
}

void	view_entries(std::string file_brake, std::string file_throttle) {
	GraphLoader	graph;
	graph.load_lt(file_brake);
	graph.load_rt(file_throttle);

	graph.run();
}

int	main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << "./analyzer.exe [file_brake] [file_throttle]" << std::endl;
		return (1);
	}

	std::string	file_brake = argv[1];
	std::string	file_throttle = argv[2];

	int	choice;

	std::cout << "What do you want :" << std::endl;
	std::cout << "  - Record entries (1)" << std::endl;
	std::cout << "  - Visualizer (2)" << std::endl;
	std::cin >> choice;

	if (choice == 1)
		record_entries(file_brake, file_throttle);
	else if (choice == 2)
		view_entries(file_brake, file_throttle);

	return (0);
}
