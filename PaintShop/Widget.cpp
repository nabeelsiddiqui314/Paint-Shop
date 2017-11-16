#include "stdafx.h"
#include "Widget.h"


Widget::Widget() {

}

void Widget::Init(sf::Vector2f size, sf::Vector2f pos, std::string filepath, Type type) {
	m_type = type;
	this->setSize(size);
	this->setPosition(pos);
	m_icon.loadFromFile("assets/" + filepath);
	this->setTexture(&m_icon);
}

bool Widget::IsClicked(sf::RenderWindow& window, sf::IntRect clicked) {
	switch (m_type) {
	case SELECT:
		if (Interface::IsClicked(window, *this, m_clock, m_delaytime, 200)) {
			m_clicked = true;
			this->setTextureRect(clicked);
		}
		return m_clicked;
		break;
	case INFINITE:
		if (Interface::IsClicked(window, *this, m_clock, m_delaytime, 0)) {
			m_clicked = true;
			this->setTextureRect(clicked);
		}
		else m_clicked = false;
		return m_clicked;
		break;
	}
}

bool Widget::IsHovered(sf::RenderWindow& window, sf::IntRect original, sf::IntRect hovered) {
	if (m_clicked || !Interface::IsHovered(window, *this)) {
		m_hovered = false;
	}
	if (Interface::IsHovered(window, *this) && !m_clicked) {
		m_hovered = true;
	}
	if (m_hovered && !m_clicked) this->setTextureRect(hovered);
	else if (!m_hovered && !m_clicked) this->setTextureRect(original);
	return m_hovered;
}


Widget::~Widget() {

}