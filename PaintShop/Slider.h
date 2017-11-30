#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include <math.h>

class Slider
{
public:
	 Slider();
	~Slider();
public:
	void AddSlider(const sf::Vector2f& pos, const double startVal, const double length, const double max, const sf::Color& color);
	int GetValue() const;
	void Update(sf::RenderWindow& window);
private:
	sf::RectangleShape m_slideSurface;
	sf::RectangleShape m_slider;
	double             m_max;
	double             m_value;
	sf::Time           m_clickTime;
	sf::Clock          m_clickClock;
};

