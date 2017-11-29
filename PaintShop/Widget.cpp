#include "stdafx.h"
#include "Widget.h"


Widget::Widget() {

}

void Widget::Init(const sf::Vector2f& size, const sf::Vector2f& pos, const std::string filepath, const sf::IntRect& crop,
	             const  sf::IntRect&  hovered, const sf::IntRect& clicked, const Type& type) {
	m_type         = type;
	m_clickRect    = clicked;
	m_hoverRect    = hovered;
	m_originalRect = crop;

	this->setSize     (size);
	this->setPosition (pos);

	m_icon.loadFromFile  ("./assets/" + filepath);
	this->setTexture     (&m_icon);
	this->setTextureRect (crop);
}

void Widget::CropWidget(sf::RenderWindow& window) {
	switch (m_type) {
	case SELECT:
		if (Interface::IsClicked(window, *this, m_clock, m_delaytime, 200)) {
			m_clicked = true;
			this->setTextureRect(m_clickRect);
		}
		break;
	case INFINITE:
		if (Interface::IsClicked(window, *this, m_clock, m_delaytime, 0)) {
			m_clicked = true;
			this->setTextureRect(m_clickRect);
		}
		else m_clicked = false;
		break;
	}

	if (m_clicked || !Interface::IsHovered(window, *this)) {
		m_hovered = false;
	}
	if (Interface::IsHovered(window, *this) && !m_clicked) {
		m_hovered = true;
	}
	if (m_hovered && !m_clicked) this->setTextureRect(m_hoverRect);
	else if (!m_hovered && !m_clicked) this->setTextureRect(m_originalRect);
}


Widget::~Widget() {

}