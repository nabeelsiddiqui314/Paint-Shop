#include "stdafx.h"
#include "Application.h"


Application::Application() {
	m_data = new Data();
	if (!m_files.Parse(m_data)) {
		return;
	}
	m_window.create(sf::VideoMode(m_data->window_size.x, m_data->window_size.y), "PaintShop");

	m_main.Initialize(m_data);
	Run();
}


void Application::Run() {
	while (m_window.isOpen()) {
		sf::Event evnt;
		while (m_window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				m_window.close();
			}
			if (evnt.type == sf::Event::Resized) {
				m_data->window_size.x = evnt.size.width;
				m_data->window_size.y = evnt.size.height;
			}
		}

		m_window.clear();   /////////////////////////////////////

		m_main.Run(m_window);

		m_window.display(); /////////////////////////////////////
	}
}


Application::~Application() {
	m_files.Write();
	delete m_data;
}
