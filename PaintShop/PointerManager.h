#pragma once
#include <SFML\Graphics.hpp>
#include "Interface.h"
#include <unordered_map>

class PointerManager
{
public:
	 PointerManager();
	~PointerManager();
public:
	void Add(std::string name, const std::string filename, const sf::Vector2f& size);
	void SetPointer(const std::string name);
	void DontDisplay();
	void Update(sf::RenderWindow& window);
private:
	std::unordered_map<std::string, sf::RectangleShape> m_pointers;
	sf::Texture m_texture;
	sf::RectangleShape* m_currentPointer = nullptr;
	sf::RectangleShape rect;
};