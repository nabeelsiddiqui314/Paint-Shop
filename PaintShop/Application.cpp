#include "stdafx.h"
#include "Application.h"


Application::Application() {
	m_window.create(sf::VideoMode(1200, 650), "PaintShop");

	m_main.Initialize();
	Run();
}


void Application::Run() {
	while (m_window.isOpen()) {
		sf::Event evnt;
		while (m_window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				m_window.close();
			}
		}

		m_window.clear();   /////////////////////////////////////

		m_main.Run(m_window);

		m_window.display(); /////////////////////////////////////
	}
}


Application::~Application() {

}
