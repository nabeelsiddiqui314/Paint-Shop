#include "stdafx.h"
#include "Paint.h"


Paint::Paint() : 
	m_toolIcons  (SELECT), 
	m_colorIcons (SELECT)
{

}


void Paint::Initialize(Data* data) {
	m_data          = data;
	m_tool          = NONE;
	m_selectedColor = BLACK;
	m_pickedColor = sf::Color(BLACK);

	m_toolIcons.Add("brush", sf::Vector2f(20, 20), sf::Vector2f(20, 20), "icons.png", sf::IntRect(0, 0, 20, 20),
		sf::IntRect(0, 20, 20, 20), sf::IntRect(0, 40, 20, 20));

	m_toolIcons.Add("pen", sf::Vector2f(20, 20), sf::Vector2f(50, 20), "icons.png", sf::IntRect(40, 0, 20, 20),
		sf::IntRect(40, 20, 20, 20), sf::IntRect(40, 40, 20, 20));

	m_toolIcons.Add("eraser", sf::Vector2f(20, 20), sf::Vector2f( 80, 20), "icons.png", sf::IntRect(20, 0, 20, 20),
		sf::IntRect(20, 20, 20, 20), sf::IntRect(20, 40, 20, 20));


	m_colorIcons.Add("colorPicker", sf::Vector2f(50, 55), sf::Vector2f(900 + (8 - 4) * 30, 20), "colorEditor.png", sf::IntRect(4, 5, 307, 309),
		sf::IntRect(6, 7, 305, 307), sf::IntRect(8, 9, 303, 305));

	for (unsigned int i = 0; i < 8; i++) {
		if (i < 4) {
			m_colorIcons.Add(m_colorsNames[i], sf::Vector2f(20, 20), sf::Vector2f(900 + i*30, 20), "ColorIcons.png", sf::IntRect(i*20, 0, 20, 20),
				sf::IntRect(i*20, 20, 20, 20), sf::IntRect(i*20, 40, 20, 20));
		}
		else {
			m_colorIcons.Add(m_colorsNames[i], sf::Vector2f(20, 20), sf::Vector2f(900 + (i - 4)*30, 50), "ColorIcons.png", sf::IntRect(i*20, 0, 20, 20),
				sf::IntRect(i*20, 20, 20, 20), sf::IntRect(i*20, 40, 20, 20));
		}
	}

	m_currentColor.setPosition(835, 20);
	m_currentColor.setSize(sf::Vector2f(50, 55));
	m_currentColor.setFillColor(sf::Color::Black);

	m_brushSlider.AddSlider(sf::Vector2f(120, 30), 10, 200, 35);

	test.setPosition(20, 20);
	test.setSize(sf::Vector2f(20, 20));
	test.setFillColor(sf::Color::Red);
}

void Paint::CheckTool() {
	if (m_toolIcons.Get("pen").IsClicked()) {
		m_tool = PEN;
	}
	if (m_toolIcons.Get("brush").IsClicked()) {
		m_tool = BRUSH;
	}
	if (m_toolIcons.Get("eraser").IsClicked()) {
		m_tool = ERASER;
	}
}

void Paint::CheckColor(sf::RenderWindow& window) {
	switch (m_selectedColor) {
	case BLACK:
		m_paintColor = sf::Color::Black;
		break;
	case WHITE:
		m_paintColor = sf::Color::White;
		break;
	case BLUE:
		m_paintColor = sf::Color::Blue;
		break;
	case RED:
		m_paintColor = sf::Color::Red;
		break;
	case GREEN:
		m_paintColor = sf::Color::Green;
		break;
	case PINK:
		m_paintColor = sf::Color::Magenta;
		break;
	case CYAN:
		m_paintColor = sf::Color::Cyan;
		break;
	case YELLOW:
		m_paintColor = sf::Color::Yellow;
		break;
	case COLOR_PICKER:
		m_paintColor = m_pickedColor;
		break;
	}
	m_currentColor.setFillColor(m_paintColor);
	window.draw(m_currentColor);
}

void Paint::Draw(sf::RenderWindow& window, const sf::IntRect& bounds, int width, int height, const sf::Color& color) {
	sf::IntRect DrawBounds = { bounds.left + width + 1, bounds.top + height + 1, bounds.width + bounds.left - width - 1, bounds.height + bounds.top - height - 1 };

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Interface::IsMouseInBounds(window, DrawBounds)) {
		for (int x = sf::Mouse::getPosition(window).x - width; x < sf::Mouse::getPosition(window).x + width; x++) {
			for (int y = sf::Mouse::getPosition(window).y - height; y < sf::Mouse::getPosition(window).y + height; y++) {
				m_data->canvas->setPixel(x - m_data->canvas_bounds.left, y - m_data->canvas_bounds.top, color);
			}
		}
	}
}

void Paint::PaintStuff(sf::RenderWindow& window) {
	switch (m_tool) {
	case BRUSH:
		Draw(window, m_data->canvas_bounds, m_brushSlider.GetValue(), m_brushSlider.GetValue(), m_paintColor);
		break;
	case PEN:
		Draw(window, m_data->canvas_bounds, m_brushSlider.GetValue() / 2, m_brushSlider.GetValue(), m_paintColor);
		break;
	case ERASER:
		Draw(window, m_data->canvas_bounds, m_brushSlider.GetValue(), m_brushSlider.GetValue(), m_data->backroundColor);
		break;
	default:
		break;
	}
}

void Paint::SelectColor() {
	for (unsigned int i = 0; i < 8; i++) {
		if (m_colorIcons.Get("colorPicker").IsClicked()) {
			m_selectedColor = COLOR_PICKER;
			RunWindow(m_colorPickerWindow, &Paint::ColorPickerWindow);
		}
		else if (m_colorIcons.Get(m_colorsNames[i]).IsClicked()) {
			m_selectedColor = (Colors)i;
		}
	}
}

void Paint::RunWindow(sf::RenderWindow& window, void (Paint::*run)()) {
	window.create(sf::VideoMode(500, 400), "ey");
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		(this->*run)();
		window.display();
	}
}

void Paint::ColorPickerWindow() {
	test.move(1, 1);
	m_colorPickerWindow.draw(test);
}

void Paint::ToolSizeWindow() {
	
}

inline void Paint::SetBgColor(const sf::Color& color) {
	m_data->canvas->create(m_data->canvas_bounds.width, m_data->canvas_bounds.height, color);
}

inline void Paint::Clear() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		SetBgColor(m_data->backroundColor);
	}
}

void Paint::Run(sf::RenderWindow& window) {
	Clear();
	CheckTool();
	CheckColor(window);
	PaintStuff(window);
	m_toolIcons.Update(window);
	m_colorIcons.Update(window);
	SelectColor();
}


Paint::~Paint() {
	
}