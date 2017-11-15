#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"
#include "Interface.h"

enum class Tool {
	NONE,
	PEN,
	BRUSH,
	FILL_BUCKET
};

class Paint
{
public:
	 Paint();
	~Paint();
public:
	void Initialize(Data* data, sf::Image& img);

	void CheckTool();
	void Draw(sf::RenderWindow& window);
	void Clear();

	void Run(sf::RenderWindow& window);
private:
	Data* m_data;
	Tool  m_tool;
};

