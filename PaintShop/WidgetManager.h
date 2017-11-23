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
	 WidgetManager();
	~WidgetManager();
public:
	void Add(std::string name, const sf::Vector2f& size, const sf::Vector2f& pos, const std::string filepath, const sf::IntRect& crop,
		                      const  sf::IntRect&  hovered, const sf::IntRect& clicked, const Type& type);
	void Update(sf::RenderWindow& window);
	const Widget& Get(const std::string name) const;
private:
	Type m_type;
	std::unordered_map <std::string, Widget> m_widgetGroup;
	Widget w;
};

