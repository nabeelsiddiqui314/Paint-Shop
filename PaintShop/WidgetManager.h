#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"
#include "Interface.h"
#include "Widget.h"
#include <unordered_map>

class WidgetManager
{
public:
	 WidgetManager(const Type& type);
	~WidgetManager();
public:
	void Add         (std::string name, const sf::Vector2f& size,    const sf::Vector2f& pos,     const std::string filepath, const sf::IntRect& crop,
		                                const sf::IntRect&  hovered, const sf::IntRect&  clicked);
	void Update      (sf::RenderWindow& window);
	const Widget& Get(const std::string name) const;
	void DeselectAll();
private:
	Type                                     m_type;
	std::unordered_map <std::string, Widget> m_widgetGroup;
	Widget                                   m_w;
	Widget*                                  m_clickedWidget = nullptr;
};

