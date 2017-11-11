#include "stdafx.h"
#include "GUI.h"


GUI::GUI() {

}


bool GUI::IsMouseInWindow(sf::RenderWindow& window) const {
	return sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < window.getSize().x &&
		   sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < window.getSize().y;
}

bool GUI::IsHovered(sf::RenderWindow& window, sf::RectangleShape& button) const {
	sf::IntRect _button(button.getPosition().x, button.getPosition().y, button.getGlobalBounds().width, button.getGlobalBounds().height);
	return _button.contains(sf::Mouse::getPosition(window));
}

bool GUI::IsClicked(sf::RenderWindow& window, sf::RectangleShape& button, int delaytime) const {
	m_delayTime = m_clock.getElapsedTime();
	if (IsHovered(window, button) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_delayTime.asMilliseconds() >= delaytime) {
		m_clock.restart();
		return true;
	}
	else {
		return false;
	}
}

void GUI::SetPointer(sf::RenderWindow& window, sf::RectangleShape& pointer, bool hideMouse) const {
	window.setMouseCursorVisible(!hideMouse);

	if (IsMouseInWindow(window)) {
		pointer.setOrigin(pointer.getGlobalBounds().width / 2, pointer.getGlobalBounds().height / 2);
		sf::Vector2f mousePos(sf::Mouse::getPosition(window));
		pointer.setPosition(mousePos);
	}
}


GUI::~GUI() {

}
