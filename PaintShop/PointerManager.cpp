#include "stdafx.h"
#include "PointerManager.h"


PointerManager::PointerManager()
{
}


void PointerManager::Add(std::string name, const std::string filename, const sf::Vector2f& size) {
	rect.setSize(size);
	m_texture.loadFromFile("./assets/pointers/" + filename);
	rect.setTexture(&m_texture);
	std::unordered_map<std::string, sf::RectangleShape>::const_iterator found = m_pointers.find(name);
	while (found != m_pointers.end()) {
		name += "0";
		found = m_pointers.find(name);
	}
	m_pointers.insert(std::make_pair(name, rect));
}

void PointerManager::SetPointer(const std::string name) {
	delete m_currentPointer;
	std::unordered_map<std::string, sf::RectangleShape>::const_iterator found = m_pointers.find(name);
	if (found != m_pointers.end()) {
		m_currentPointer = new sf::RectangleShape();
		*m_currentPointer = found->second;
	}
}

void PointerManager::DontDisplay() {
	delete m_currentPointer;
	m_currentPointer = nullptr;
}

void PointerManager::Update(sf::RenderWindow& window) {
	if (m_currentPointer != nullptr) {
		Interface::SetPointer(window, *m_currentPointer, true);
	}
	else {
		window.setMouseCursorVisible(true);
	}
}


PointerManager::~PointerManager()
{
}
