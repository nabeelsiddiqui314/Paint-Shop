#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"
#include "Interface.h"
#include "Widget.h"
#include "WidgetManager.h"

enum Tool {
	NONE,
	PEN,
	BRUSH,
	ERASER,
	FILL_BUCKET
};

enum Colors {
	BLACK,
	WHITE,
	BLUE,
	RED,
	GREEN,
	PINK,
	CYAN,
	YELLOW
};

class Paint
{
public:
	 Paint();
	~Paint();
public:
	void Initialize (Data* data, sf::Image& img);
	void Run(sf::RenderWindow& window);
private:
	void CheckTool();
	void CheckColor();
	void Draw(sf::RenderWindow& window, const sf::IntRect& bounds, int width, int height, const sf::Color& color);
	void PaintStuff(sf::RenderWindow& window);
	void SelectColor();
	inline void Clear();
	inline void SetBgColor(const sf::Color& color);
private:
	Data*         m_data;
	Tool          m_tool;
	WidgetManager m_toolIcons;
	Colors        m_selectedColor;
	WidgetManager m_colorIcons;
	sf::Color     m_paintColor;

	std::string m_colorsNames[8] = { 
		"BLACK",
		"WHITE",
		"BLUE",
		"RED",
		"GREEN",
		"PINK",
		"CYAN",
		"YELLOW",
	};
};