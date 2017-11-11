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
	void Initialize(Data* data); //gets called in application once

	void Render(sf::RenderWindow& window);

	void Run(sf::RenderWindow& window); // gets called in application loop every frame
private:
	Data*              m_data;
	sf::Image          m_canvas;
	sf::Texture        m_canvasTexture;
	sf::RectangleShape m_backround;
};

