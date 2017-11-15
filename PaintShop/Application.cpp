#include "stdafx.h"
#include "Application.h"


Application::Application() {
	m_data = new Data();
	m_data->canvas = &m_canvas;
	if (!m_files.Parse(m_data)) {
		return;
	}
	m_window.create(sf::VideoMode(m_data->window_size.x, m_data->window_size.y), "PaintShop");

	m_canvas.create(m_data->window_size.x, m_data->window_size.y, m_data->backroundColor);
	m_canvasRect.setPosition(0, 0);
	m_canvasRect.setSize(sf::Vector2f(m_data->window_size.x, m_data->window_size.y));
	m_main.Initialize(m_data, m_canvas);
	Run();
}

inline void Application::UpdateCanvas() {
	m_canvasRect.setPosition(m_data->canvas_startPos.x, m_data->canvas_startPos.y);
	m_canvasRect.setSize(sf::Vector2f(m_canvas.getSize()));
	m_canvasTexture.loadFromImage(m_canvas);
	m_canvasRect.setTexture(&m_canvasTexture);
	m_window.draw(m_canvasRect);
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

		UpdateCanvas();
		m_main.Run(m_window);

		m_window.display(); /////////////////////////////////////
	}
}


Application::~Application() {
	m_files.Write();
	delete m_data;
}
