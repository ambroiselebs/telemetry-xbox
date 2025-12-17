#include "OutFile.hpp"

OutFile::OutFile(const std::string& filename) : file_name(filename) {
	this->file.open(this->file_name, std::ios::out | std::ios::app);
	if (!this->file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
	}
}
OutFile::~OutFile() {
	if (this->file.is_open())
		this->file.close();
}

std::vector<std::string>	OutFile::read_lines() {
	std::vector<std::string>	lines;
	std::string					line;

	while (std::getline(this->file, line))
		lines.push_back(line);
	return (lines);
}
