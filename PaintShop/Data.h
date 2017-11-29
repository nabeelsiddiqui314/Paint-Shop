#pragma once
#include <SFML/Graphics.hpp>

struct Data {
	sf::Color    backroundColor;
	sf::Image*   canvas;
	sf::Vector2i window_size;
	sf::IntRect  canvas_bounds = { 40, 60, 800, 550 };
};