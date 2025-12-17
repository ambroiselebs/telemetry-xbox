#ifndef OUTFILE_HPP
# define OUTFILE_HPP

# include <iostream>
# include <string>
# include <fstream>
# include <vector>

class OutFile
{
private:
	std::string		file_name;
	std::fstream	file;
public:
	OutFile(const std::string& filename);
	~OutFile();

	bool	open_read() {
		this->file.open(this->file_name, std::ios::in);
		return this->file.is_open();
	}
	bool	open_write() {
		this->file.open(this->file_name, std::ios::out | std::ios::trunc);
		return this->file.is_open();
	}

	void	close() {
		if (this->file.is_open())
			this->file.close();
	}

	void	write(const std::string& content) {
		this->file << content;
	}
	void	write_line(const std::string& content) {
		this->file << content << std::endl;
	}

	std::vector<std::string>	read_lines();
};

#endif
