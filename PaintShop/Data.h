#pragma once
#include <SFML/Graphics.hpp>

struct Data {
	sf::Color    backroundColor;
	sf::Image*   canvas;
	sf::Vector2i window_size;
	sf::Vector2i canvas_startPos = { 0, 0 };
};