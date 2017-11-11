#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class GUI
{
public:
	 GUI();
	~GUI();
public:
	bool IsMouseInWindow (sf::RenderWindow& window)                                              const;
	bool IsHovered       (sf::RenderWindow& window, sf::RectangleShape& button)                  const;
	bool IsClicked       (sf::RenderWindow& window, sf::RectangleShape& button, int delaytime)   const;
	void SetPointer      (sf::RenderWindow& window, sf::RectangleShape& pointer, bool hideMouse) const;
private:
	mutable sf::Clock m_clock;
	mutable sf::Time  m_delayTime;
};

