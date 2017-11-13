#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"
#include "GUI.h"

class Paint
{
public:
	 Paint();
	~Paint();
public:
	void Initialize(Data* data, sf::Image& img);

	void Run(sf::RenderWindow& window);
private:
	Data* m_data;
};

