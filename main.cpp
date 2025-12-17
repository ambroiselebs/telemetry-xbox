#include <iostream>
#include "Controller.hpp"
#include "GraphLoader.hpp"

void	record_entries() {
	OutFile		outfile_lt("out/test/brake");
	OutFile		outfile_rt("out/test/throttle");
	Controller	controller(outfile_lt, outfile_rt);

	controller.loop();
}

void	view_entries() {
	GraphLoader	graph;
	graph.load_lt("out/test/brake");
	graph.load_rt("out/test/throttle");

	graph.run();
}

int	main() {
	int	choice;

	std::cout << "What do you want :" << std::endl;
	std::cout << "  - Record entries (1)" << std::endl;
	std::cout << "  - Visualizer (2)" << std::endl;
	std::cin >> choice;

	if (choice == 1)
		record_entries();
	else if (choice == 2)
		view_entries();

	return (0);
}
