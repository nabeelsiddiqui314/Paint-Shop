#include "stdafx.h"
#include "WidgetManager.h"


WidgetManager::WidgetManager(const Type& type) : m_type(type) {
	
}


void WidgetManager::Add(std::string name, const sf::Vector2f& size, const sf::Vector2f& pos, const std::string filepath, const sf::IntRect& crop,
	const sf::IntRect& hovered, const sf::IntRect& clicked) {
	m_w.Init(size, pos, filepath, crop, hovered, clicked, m_type);

	std::unordered_map <std::string, Widget>::const_iterator found = m_widgetGroup.find(name);
	while (found != m_widgetGroup.end()) {
		name += "0";
		found = m_widgetGroup.find(name);
	}
	m_widgetGroup.insert(std::make_pair(name, m_w));
}

void WidgetManager::Update(sf::RenderWindow& window) {
	if (m_type == SELECT) {
		for (auto& iterator : m_widgetGroup) {
			iterator.second.CropWidget(window);
			if (iterator.second.IsClicked()) {
				m_clickedWidget = &iterator.second;
			}
			if (m_clickedWidget != nullptr) {
				for (auto& unclickedIterator : m_widgetGroup) {
					if (&unclickedIterator.second != m_clickedWidget) unclickedIterator.second.Deselect();
				}
			}
			window.draw(iterator.second);
		}
	}

	else if (m_type == INFINITE) {
		for (auto& iterator : m_widgetGroup) {
			iterator.second.CropWidget(window);
			window.draw(iterator.second);
		}
	}
}

void WidgetManager::DeselectAll() {
	for (auto& all : m_widgetGroup) {
		all.second.Deselect();
	}
}

const Widget& WidgetManager::Get(const std::string name) const {
	std::unordered_map <std::string, Widget>::const_iterator found = m_widgetGroup.find(name);
	if (found == m_widgetGroup.end()) {
		Widget temp;
		return temp;
	}
	else
		return found->second;
}


WidgetManager::~WidgetManager() {
	m_widgetGroup.clear();
}
