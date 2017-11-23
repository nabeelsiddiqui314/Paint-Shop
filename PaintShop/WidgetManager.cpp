#include "stdafx.h"
#include "WidgetManager.h"


WidgetManager::WidgetManager() {
	
}


void WidgetManager:: Add(std::string name, const sf::Vector2f& size, const sf::Vector2f& pos, const std::string filepath, const sf::IntRect& crop,
	const  sf::IntRect&  hovered, const sf::IntRect& clicked, const Type& type) {
	m_type = type;
	w.Init(size, pos, filepath, crop, hovered, clicked, type);

	std::unordered_map <std::string, Widget>::const_iterator found = m_widgetGroup.find(name);
	while (found != m_widgetGroup.end()) {
		name += "0";
		found = m_widgetGroup.find(name);
	}
	m_widgetGroup.insert(std::make_pair(name, w));
}

void WidgetManager::Update(sf::RenderWindow& window) {
	for (auto& iterator : m_widgetGroup) {
		iterator.second.CropWidget(window);
		window.draw(iterator.second);
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

}
