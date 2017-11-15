#include "stdafx.h"
#include "Paint.h"


Paint::Paint() {

}


void Paint::Initialize(Data* data, sf::Image& img) {
	m_data = data;
	m_tool = Tool::NONE;
}

void Paint::CheckTool() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		m_tool = Tool::PEN;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		m_tool = Tool::BRUSH;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
		m_tool = Tool::NONE;
	}
}

void Paint::Draw(sf::RenderWindow& window) {
	switch (m_tool) {
	case Tool::PEN:
		if (Interface::IsMouseInBounds(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			m_data->canvas->setPixel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, sf::Color::Green);
		}
		break;
	case Tool::BRUSH:
		if (Interface::IsMouseInBounds(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			for (int x = sf::Mouse::getPosition(window).x - 3; x < sf::Mouse::getPosition(window).x + 3; x++) {
				for (int y = sf::Mouse::getPosition(window).y - 10; y < sf::Mouse::getPosition(window).y + 10; y++) {
					/*if (x > sf::Mouse::getPosition(window).x - 5) {
						break;
					}*/
					m_data->canvas->setPixel(x, y, sf::Color::Blue);
				}
			}
		}
		break;
	default:
		break;
	}
}

void Paint::Clear() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		m_data->canvas->create(m_data->window_size.x, m_data->window_size.y, m_data->backroundColor);
	}
}

void Paint::Run(sf::RenderWindow& window) {
	Clear();
	CheckTool();
	Draw(window);
}


Paint::~Paint() {
	
}
