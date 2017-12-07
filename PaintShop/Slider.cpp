#include "stdafx.h"
#include "Slider.h"


Slider::Slider()
{
}


void Slider::AddSlider(const sf::Vector2f& pos, const double startVal, const double length, const double max) {
	m_max   = max;
	m_value = startVal;
	sliderTex.loadFromFile("./assets/slider.png");
	sliderSurfaceTex.loadFromFile("./assets/SliderSurface.png");

	m_slideSurface.setSize(sf::Vector2f(length, 5));
	m_slideSurface.setPosition(pos);
	m_slideSurface.setTexture(&sliderSurfaceTex);

	m_slider.setSize(sf::Vector2f(5, 10));
	m_slider.setPosition(((m_slideSurface.getGlobalBounds().width)/max * startVal) + m_slideSurface.getPosition().x,
		                   m_slideSurface.getPosition().y + m_slideSurface.getGlobalBounds().height);
	m_slider.setOrigin(m_slider.getSize().x / 2, 0);
	m_slider.setTexture(&sliderTex);
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
		m_slider.setPosition(sf::Mouse::getPosition(window).x, m_slideSurface.getPosition().y + m_slideSurface.getGlobalBounds().height);
	}
	m_value = (m_slider.getPosition().x - m_slideSurface.getPosition().x ) / (m_slideSurface.getGlobalBounds().width) * m_max;

	window.draw(m_slideSurface);
	window.draw(m_slider);
}


Slider::~Slider()
{
}
