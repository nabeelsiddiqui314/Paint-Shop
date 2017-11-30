#include "stdafx.h"
#include "Slider.h"


Slider::Slider()
{
}


void Slider::AddSlider(const sf::Vector2f& pos, const double startVal, const double length, const double max, const sf::Color& color) {
	m_max   = max;
	m_value = startVal;

	m_slideSurface.setSize(sf::Vector2f(length, 5));
	m_slideSurface.setPosition(pos);
	m_slideSurface.setFillColor(color);

	m_slider.setSize(sf::Vector2f(5, 10));
	m_slider.setPosition(((m_slideSurface.getGlobalBounds().width)/max * startVal) + m_slideSurface.getPosition().x,
		                   m_slideSurface.getPosition().y + m_slideSurface.getGlobalBounds().height/2);
	m_slider.setFillColor(color);
}

int Slider::GetValue() const {
	int value = ceil(m_value);
	return value;
}

void Slider::Update(sf::RenderWindow& window) {
	if (Interface::IsMouseInBounds(window, sf::IntRect(m_slideSurface.getPosition().x, m_slideSurface.getPosition().y - 20,
		m_slideSurface.getPosition().x + m_slideSurface.getGlobalBounds().width, m_slideSurface.getPosition().y + m_slideSurface.getGlobalBounds().height + 20))
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		m_slider.setPosition(sf::Mouse::getPosition(window).x, m_slideSurface.getPosition().y + m_slideSurface.getGlobalBounds().height / 2);
	}
	m_value = (m_slider.getPosition().x - m_slideSurface.getPosition().x ) / (m_slideSurface.getGlobalBounds().width) * m_max;

	window.draw(m_slideSurface);
	window.draw(m_slider);
}


Slider::~Slider()
{
}
