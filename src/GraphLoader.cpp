#include "GraphLoader.hpp"
#include <iostream>

GraphLoader::GraphLoader() : window(sf::VideoMode(1200, 500), "Telemetry - LT (Red) / RT (Blue)") ,scroll_offset(0) ,zoom(3.0f) {
	this->window.setFramerateLimit(60);
}

GraphLoader::~GraphLoader() {
	if (this->window.isOpen())
		this->window.close();
}

bool	GraphLoader::load_file(const std::string& filename, std::vector<DataPoint>& data) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		DataPoint point;
		std::stringstream ss(line);
		std::string percent_str;
		std::string trigger;

		std::getline(ss, point.time, ',');
		std::getline(ss, percent_str, ',');
		std::getline(ss, trigger, ',');

		point.percent = std::stoi(percent_str);
		data.push_back(point);
	}

	file.close();
	std::cout << "Loaded " << data.size() << " points from " << filename << std::endl;
	return true;
}

bool	GraphLoader::load_lt(const std::string& filename) {
	return this->load_file(filename, this->lt_data);
}

bool	GraphLoader::load_rt(const std::string& filename) {
	return this->load_file(filename, this->rt_data);
}

void	GraphLoader::run() {
	while (this->window.isOpen()) {
		sf::Event event;
		while (this->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				this->window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up)
					this->zoom += 0.5f;
				if (event.key.code == sf::Keyboard::Down)
					this->zoom -= 0.5f;
				if (this->scroll_offset < 0)
					this->scroll_offset = 0;
				if (this->zoom < 0.5f)
					this->zoom = 0.5f;
			}
			if (event.type == sf::Event::MouseWheelScrolled) {
				this->scroll_offset -= event.mouseWheelScroll.delta * 30;
				if (this->scroll_offset < 0)
					this->scroll_offset = 0;
			}
		}

		this->window.clear(sf::Color(20, 20, 20));

		// Grille horizontale (0%, 25%, 50%, 75%, 100%)
		for (int i = 0; i <= 100; i += 25) {
			float y = 450 - (i * 4);
			sf::Vertex grid[] = {
				sf::Vertex(sf::Vector2f(0, y), sf::Color(50, 50, 50)),
				sf::Vertex(sf::Vector2f(1200, y), sf::Color(50, 50, 50))
			};
			this->window.draw(grid, 2, sf::Lines);
		}

		// Ligne LT (rouge)
		if (this->lt_data.size() > 1) {
			sf::VertexArray lt_line(sf::LineStrip);
			for (size_t i = this->scroll_offset; i < this->lt_data.size(); i++) {
				float x = (float)(i - this->scroll_offset) * this->zoom;
				if (x > 1200)
					break;
				float y = 450 - (this->lt_data[i].percent * 4);
				lt_line.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Red));
			}
			this->window.draw(lt_line);
		}

		// Ligne RT (bleu)
		if (this->rt_data.size() > 1) {
			sf::VertexArray rt_line(sf::LineStrip);
			for (size_t i = this->scroll_offset; i < this->rt_data.size(); i++) {
				float x = (float)(i - this->scroll_offset) * this->zoom;
				if (x > 1200)
					break;
				float y = 450 - (this->rt_data[i].percent * 4);
				rt_line.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Cyan));
			}
			this->window.draw(rt_line);
		}

		// Légende
		sf::RectangleShape lt_legend(sf::Vector2f(20, 3));
		lt_legend.setFillColor(sf::Color::Red);
		lt_legend.setPosition(10, 15);
		this->window.draw(lt_legend);

		sf::RectangleShape rt_legend(sf::Vector2f(20, 3));
		rt_legend.setFillColor(sf::Color::Cyan);
		rt_legend.setPosition(10, 35);
		this->window.draw(rt_legend);

		this->window.display();
	}
}
