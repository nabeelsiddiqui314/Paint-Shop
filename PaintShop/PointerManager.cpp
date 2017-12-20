#include "stdafx.h"
#include "PointerManager.h"


PointerManager::PointerManager()
{
}


void PointerManager::Add(std::string name, const std::string filename, const sf::Vector2f& size) {
	m_pointer = new Pointer();
	m_pointer->rect.setSize(size);
	m_pointer->tex.loadFromFile("./assets/pointers/" + filename);
	m_pointer->rect.setTexture(&m_pointer->tex);
	std::unordered_map<std::string, Pointer>::const_iterator found = m_pointers.find(name);
	while (found != m_pointers.end()) {
		name += "0";
		found = m_pointers.find(name);
	}
	m_pointers.insert(std::make_pair(name, *m_pointer));
}

void PointerManager::SetPointer(const std::string name) {
	delete m_currentPointer;
	std::unordered_map<std::string, Pointer>::const_iterator found = m_pointers.find(name);
	if (found != m_pointers.end()) {
		m_currentPointer = new Pointer();
		*m_currentPointer = found->second;
	}
}

void PointerManager::DontDisplay() {
	delete m_currentPointer;
	m_currentPointer = nullptr;
}

void PointerManager::Update(sf::RenderWindow& window) {
	if (m_currentPointer != nullptr) {
		Interface::SetPointer(window, m_currentPointer->rect, true);
	}
	else {
		window.setMouseCursorVisible(true);
	}
}


PointerManager::~PointerManager()
{
}
