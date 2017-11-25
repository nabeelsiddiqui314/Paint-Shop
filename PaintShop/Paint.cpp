#include "stdafx.h"
#include "Paint.h"


Paint::Paint() : m_toolIcons(SELECT) {

}


void Paint::Initialize(Data* data, sf::Image& img) {
	m_data = data;
	m_tool = NONE;

	m_canvasBounds = { 0, 70, m_data->window_size.x, m_data->window_size.y };

	m_toolIcons.Add("brush", sf::Vector2f(20, 20), sf::Vector2f(20, 20), "icons.png", sf::IntRect(0, 0, 20, 20),
		sf::IntRect(0, 20, 20, 20), sf::IntRect(0, 40, 20, 20));

	m_toolIcons.Add("pen", sf::Vector2f(20, 20), sf::Vector2f(50, 20), "icons.png", sf::IntRect(40, 0, 20, 20),
		sf::IntRect(40, 20, 20, 20), sf::IntRect(40, 40, 20, 20));

	m_toolIcons.Add("eraser", sf::Vector2f(20, 20), sf::Vector2f( 80, 20), "icons.png", sf::IntRect(20, 0, 20, 20),
		sf::IntRect(20, 20, 20, 20), sf::IntRect(20, 40, 20, 20));
}

void Paint::CheckTool() {
	if (m_toolIcons.Get("pen").IsClicked()) {
		m_tool = PEN;
	}
	if (m_toolIcons.Get("brush").IsClicked()) {
		m_tool = BRUSH;
	}
	if (m_toolIcons.Get("eraser").IsClicked()) {
		m_tool = ERASER;
	}
}

void Paint::Draw(sf::RenderWindow& window, const sf::IntRect& bounds, unsigned int width, unsigned int height, const sf::Color& color) {
	if (Interface::IsMouseInBounds(window, bounds) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		for (int x = sf::Mouse::getPosition(window).x - width; x < sf::Mouse::getPosition(window).x + width; x++) {
			for (int y = sf::Mouse::getPosition(window).y - height; y < sf::Mouse::getPosition(window).y + height; y++) {
				m_data->canvas->setPixel(x, y, color);
			}
		}
	}
}

void Paint::Draw(sf::RenderWindow& window, unsigned int width, unsigned int height, const sf::Color& color) {
	if (Interface::IsMouseInBounds(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		for (int x = sf::Mouse::getPosition(window).x - width; x < sf::Mouse::getPosition(window).x + width; x++) {
			for (int y = sf::Mouse::getPosition(window).y - height; y < sf::Mouse::getPosition(window).y + height; y++) {
				m_data->canvas->setPixel(x, y, color);
			}
		}
	}
}

void Paint::PaintStuff(sf::RenderWindow& window) {
	switch (m_tool) {
	case BRUSH:
		Draw(window, m_canvasBounds, 10, 10, sf::Color::Green);
		break;
	case PEN:
		Draw(window, m_canvasBounds, 4, 10, sf::Color::Blue);
		break;
	case ERASER:
		Draw(window, m_canvasBounds, 4, 10, m_data->backroundColor);
		break;
	default:
		break;
	}
}

inline void Paint::SetBgColor(const sf::Color& color) {
	m_data->canvas->create(m_data->window_size.x, m_data->window_size.y, color);
}

inline void Paint::Clear() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		SetBgColor(m_data->backroundColor);
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
