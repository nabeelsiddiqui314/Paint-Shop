#include "stdafx.h"
#include "Paint.h"


Paint::Paint() {

}


void Paint::Initialize(Data* data, sf::Image& img) {
	m_data = data;
	m_tool = NONE;

	m_toolIcons.Add("brush", sf::Vector2f(20, 20), sf::Vector2f(20, 20), "icons.png", sf::IntRect(0, 0, 20, 20),
		sf::IntRect(0, 20, 20, 20), sf::IntRect(0, 40, 20, 20), SELECT);

	m_toolIcons.Add("eraser", sf::Vector2f(20, 20), sf::Vector2f( 50, 20), "icons.png", sf::IntRect(20, 0, 20, 20),
		sf::IntRect(20, 20, 20, 20), sf::IntRect(20, 40, 20, 20), SELECT);
}

void Paint::CheckTool() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		m_tool = PEN;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		m_tool = BRUSH;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
		m_tool = NONE;
	}
}

void Paint::PaintStuff(sf::RenderWindow& window) {
	switch (m_tool) {
	case PEN:
		if (Interface::IsMouseInBounds(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			m_data->canvas->setPixel(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, sf::Color::Green);
		}
		break;
	case BRUSH:
		if (Interface::IsMouseInBounds(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			for (int x = sf::Mouse::getPosition(window).x - 3; x < sf::Mouse::getPosition(window).x + 3; x++) {
				for (int y = sf::Mouse::getPosition(window).y - 10; y < sf::Mouse::getPosition(window).y + 10; y++) {
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
	PaintStuff(window);
	m_toolIcons.Update(window);
}


Paint::~Paint() {
	
}
