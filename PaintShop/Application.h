#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Paint.h"
#include "Data.h"
#include "FileParser.h"

class Application
{
public:
	 Application();
	~Application();
public:
	inline void UpdateCanvas();
	void Run();
private:
	sf::RenderWindow   m_window;
	Data*              m_data;
	FileParser         m_files;
	Paint              m_main;

	sf::Image          m_canvas;
	sf::Texture        m_canvasTexture;
	sf::RectangleShape m_canvasRect;
};

