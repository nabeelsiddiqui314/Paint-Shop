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

class Paint
{
public:
	 Paint();
	~Paint();
public:
	void Initialize (Data* data, sf::Image& img);

	void CheckTool ();
	void Draw(sf::RenderWindow& window, const sf::IntRect& bounds, int width, int height, const sf::Color& color);
	void PaintStuff (sf::RenderWindow& window);
	inline void Clear ();
	inline void SetBgColor(const sf::Color& color);

	void Run(sf::RenderWindow& window);
private:
	Data*         m_data;
	Tool          m_tool;
	WidgetManager m_toolIcons;
};