#include "stdafx.h"
#include "Interface.h"


Interface::Interface() {

}


bool Interface::IsMouseInBounds(sf::RenderWindow& window) {
	return sf::Mouse::getPosition(window).x >= 0 && sf::Mouse::getPosition(window).x <= window.getSize().x &&
		   sf::Mouse::getPosition(window).y >= 0 && sf::Mouse::getPosition(window).y <= window.getSize().y;
}

bool Interface::IsMouseInBounds(sf::RenderWindow& window, sf::IntRect bounds) {
	return sf::Mouse::getPosition(window).x >= bounds.left && sf::Mouse::getPosition(window).x <= bounds.width  + bounds.left &&
		   sf::Mouse::getPosition(window).y >= bounds.top  && sf::Mouse::getPosition(window).y <= bounds.height + bounds.top;
}

bool Interface::IsHovered(sf::RenderWindow& window, sf::RectangleShape& button) {
	sf::IntRect _button(button.getPosition().x, button.getPosition().y, button.getGlobalBounds().width, button.getGlobalBounds().height);
	return _button.contains(sf::Mouse::getPosition(window));
}

bool Interface::IsClicked(sf::RenderWindow& window, sf::RectangleShape& button, sf::Clock& clock, sf::Time& delaytimeVar, int delaytime) {
	delaytimeVar = clock.getElapsedTime();
	if (delaytimeVar.asMilliseconds() > delaytime && IsHovered(window, button) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		clock.restart();
		return true;
	}
	return false; // no need of "else" because return true exits the function
}

void Interface::SetPointer(sf::RenderWindow& window, sf::RectangleShape& pointer, bool hideMouse) {
	window.setMouseCursorVisible(!hideMouse);

	sf::Vector2f mousePos(sf::Mouse::getPosition(window));
	pointer.setPosition(mousePos);

	window.draw(pointer);
}


Interface::~Interface() {

}
