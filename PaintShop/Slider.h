#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include <math.h>

struct Rectangle {
	sf::RectangleShape rect;
	sf::Texture tex;
	double x, y, w, h;
};

class Slider
{
public:
	 Slider();
	~Slider();
public:
	void AddSlider(const sf::Vector2f& pos, const double startVal, const double length, const double max);
	int GetValue() const;
	void Update(sf::RenderWindow& window);
private:
	Rectangle m_slideSurface;
	Rectangle m_slider;
	double             m_max;
	double             m_value;
	sf::Time           m_clickTime;
	sf::Clock          m_clickClock;
};

