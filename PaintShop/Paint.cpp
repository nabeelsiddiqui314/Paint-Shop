#include "stdafx.h"
#include "Paint.h"


Paint::Paint() {

}


void Paint::Initialize(Data* data) {
	m_data = data;
	m_canvas.create(m_data->window_size.x - 100, m_data->window_size.y -100, sf::Color::White);
	m_canvasRect.setPosition(50, 50);
	m_canvasRect.setSize(sf::Vector2f(m_data->window_size.x - 100, m_data->window_size.y - 100));
}


void Paint::Render(sf::RenderWindow& window) {
	m_canvasTexture.loadFromImage(m_canvas);
	m_canvasRect.setTexture(&m_canvasTexture);
	window.draw(m_canvasRect);
}

void Paint::Run(sf::RenderWindow& window) {
	Render(window);
}


Paint::~Paint() {
	
}
