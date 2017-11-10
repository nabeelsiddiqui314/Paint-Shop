#include "stdafx.h"
#include "Paint.h"


Paint::Paint() {

}


void Paint::Initialize() {
	m_canvas.create(1200, 650, sf::Color::White);
	m_backround.setPosition(0, 0);
	m_backround.setSize(sf::Vector2f(1200, 650));
}


void Paint::Render(sf::RenderWindow& window) {
	m_canvasTexture.loadFromImage(m_canvas);
	m_backround.setTexture(&m_canvasTexture);
	window.draw(m_backround);
}

void Paint::Run(sf::RenderWindow& window) {
	Render(window);
}


Paint::~Paint() {

}
