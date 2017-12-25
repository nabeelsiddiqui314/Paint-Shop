#include "stdafx.h"
#include "Slider.h"


Slider::Slider()
{
}


void Slider::AddSlider(const sf::Vector2f& pos, const double startVal, const double length, const double max) {
	m_max   = max;
	m_value = startVal;
	m_slider.tex.loadFromFile("./assets/slider.png");
	m_slideSurface.tex.loadFromFile("./assets/SliderSurface.png");

	m_slideSurface.rect.setSize(sf::Vector2f(length, 5));
	m_slideSurface.rect.setPosition(pos);
	m_slideSurface.rect.setTexture(&m_slideSurface.tex);

	m_slider.rect.setSize(sf::Vector2f(5, 10));
	m_slider.rect.setPosition(((m_slideSurface.rect.getGlobalBounds().width)/max * startVal) + m_slideSurface.rect.getPosition().x,
		                   m_slideSurface.rect.getPosition().y + m_slideSurface.rect.getGlobalBounds().height);
	m_slider.rect.setOrigin(m_slider.rect.getSize().x / 2, 0);
	m_slider.rect.setTexture(&m_slider.tex);
}

int Slider::GetValue() const {
	int value = ceil(m_value);
	return value;
}

void Slider::Update(sf::RenderWindow& window) {
	m_slider.x = m_slider.rect.getPosition().x;
	m_slider.y = m_slider.rect.getPosition().y;
	m_slider.w = m_slider.rect.getGlobalBounds().width;
	m_slider.h = m_slider.rect.getGlobalBounds().height;

	m_slideSurface.x = m_slideSurface.rect.getPosition().x;
	m_slideSurface.y = m_slideSurface.rect.getPosition().y;
	m_slideSurface.w = m_slideSurface.rect.getGlobalBounds().width;
	m_slideSurface.h = m_slideSurface.rect.getGlobalBounds().height;

	if (Interface::IsMouseInBounds(window, sf::IntRect(m_slideSurface.x, m_slideSurface.y - 20,
		m_slideSurface.w, m_slideSurface.h + 40))
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		m_slider.rect.setPosition(sf::Mouse::getPosition(window).x, m_slideSurface.y + m_slideSurface.h);
	}
	m_value = (m_slider.x - m_slideSurface.x ) / (m_slideSurface.w) * m_max;

	window.draw(m_slideSurface.rect);
	window.draw(m_slider.rect);
}


Slider::~Slider()
{
}
