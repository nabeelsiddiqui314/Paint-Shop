#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
	std::cout << "C++ works!" << std::endl;

	sf::RenderWindow window;
	window.create(sf::VideoMode(1200, 650), "Sfml works!");

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}
			window.clear();
			window.display();
		}
	}
    return 0;
}

