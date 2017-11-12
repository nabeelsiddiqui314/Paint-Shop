#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class GUI
{
public:
	 GUI();
	~GUI();
public:
	static bool IsMouseInBounds (sf::RenderWindow& window);                       //overload: will check if mouse is in window 
	static bool IsMouseInBounds (sf::RenderWindow& window, sf::IntRect bounds);   //overload: will check if mouse is in specified bounds
	static bool IsHovered       (sf::RenderWindow& window, sf::RectangleShape& button);
	static bool IsClicked       (sf::RenderWindow& window, sf::RectangleShape& button, sf::Clock& clock, sf::Time& delaytimeVar, int delaytime);
	static void SetPointer      (sf::RenderWindow& window, sf::RectangleShape& pointer, bool hideMouse);
};

