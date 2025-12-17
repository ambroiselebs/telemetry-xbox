#ifndef GRAPH_LOADER_HPP
# define GRAPH_LOADER_HPP

# include <vector>
# include <string>
# include <fstream>
# include <sstream>
# include <SFML/Graphics.hpp>

struct DataPoint {
	std::string	time;
	int			percent;
};

class GraphLoader {
	private:
		sf::RenderWindow		window;
		std::vector<DataPoint>	lt_data;
		std::vector<DataPoint>	rt_data;
		int						scroll_offset;
		float					zoom;

	public:
		GraphLoader();
		~GraphLoader();

		bool	load_file(const std::string& filename, std::vector<DataPoint>& data);
		bool	load_lt(const std::string& filename);
		bool	load_rt(const std::string& filename);
		void	run();
};

#endif
