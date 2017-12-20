#pragma once
#include <SFML\Graphics.hpp>
#include "Interface.h"
#include <unordered_map>
#include <vector>

struct Pointer {
	sf::RectangleShape rect;
	sf::Texture tex;
};

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
	std::unordered_map<std::string, Pointer> m_pointers;
	Pointer* m_currentPointer = nullptr;
	Pointer* m_pointer;
};