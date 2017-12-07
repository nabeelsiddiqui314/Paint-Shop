#include "stdafx.h"
#include "Application.h"


Application::Application() {
	m_data = new Data();
	m_data->canvas = &m_canvas;
	if (!m_files.Parse(m_data)) {
		return;
	}
	m_window.create(sf::VideoMode(m_data->window_size.x, m_data->window_size.y), "PaintShop", sf::Style::Close);

	m_canvas.create(m_data->canvas_bounds.width, m_data->canvas_bounds.height, m_data->backroundColor);
	m_canvasRect.setPosition(0, 0);
	m_canvasRect.setSize(sf::Vector2f(m_data->window_size.x, m_data->window_size.y));
	m_paint.Initialize(m_data);
	Run();
}

inline void Application::UpdateCanvas() {
	m_canvasRect.setPosition(m_data->canvas_bounds.left, m_data->canvas_bounds.top);
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

		m_window.clear(sf::Color(58, 57, 68));   /////////////////////////////////////

		UpdateCanvas();
		m_paint.Run(m_window);

		m_window.display(); /////////////////////////////////////
	}
}


Application::~Application() {
	m_files.Write();
	delete m_data;
}
