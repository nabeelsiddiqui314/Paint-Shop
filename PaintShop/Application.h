#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Paint.h"

class Application
{
public:
	 Application();
	~Application();
public:
	void Run();
private:
	sf::RenderWindow m_window;
	Paint            m_main;
};

