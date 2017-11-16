#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"
#include "Interface.h"

enum Type {
	SELECT,
	INFINITE
};

class Widget : public sf::RectangleShape
{
public:
	 Widget();
	~Widget();
public:
	void Init      (sf::Vector2f size, sf::Vector2f pos, std::string filepath, Type type);

	bool IsClicked (sf::RenderWindow& window, sf::IntRect   clicked);
	bool IsHovered (sf::RenderWindow& window, sf::IntRect   original, sf::IntRect   hovered);
private:
	sf::Texture m_icon;
	sf::Clock   m_clock;
	sf::Time    m_delaytime;
	Type        m_type;
	bool        m_clicked,
		        m_hovered;
};

