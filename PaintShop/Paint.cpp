#include "stdafx.h"
#include "Paint.h"


Paint::Paint() {

}


void Paint::Initialize(Data* data) {
	m_data = data;
	m_canvas.create(m_data->window_size.x, m_data->window_size.y, sf::Color::Yellow);
	m_backround.setPosition(0, 0);
	m_backround.setSize(sf::Vector2f(m_data->window_size.x, m_data->window_size.y));
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
