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
	void Run();
private:
	sf::RenderWindow m_window;
	Paint            m_main;
	Data*            m_data;
	FileParser       m_files;
};

