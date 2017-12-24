#pragma once
#include <SFML/Graphics.hpp>

struct Data {
	sf::Color    backroundColor;
	sf::Image*   canvas;
	sf::Vector2i window_size;
	sf::IntRect  canvas_bounds = { 80, 85, 1100, 540 };
	uint64_t img_number;
};