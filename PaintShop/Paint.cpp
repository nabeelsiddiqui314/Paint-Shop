#include "stdafx.h"
#include "Paint.h"


Paint::Paint(sf::RenderWindow& window) : 
	m_windows (window),
	m_Ok_cancel_cp(sf::Vector2f(50, 450), sf::Vector2f(150, 450))
{
	
}


// inits ------------------------------------------

inline void Paint::init_toolIcons() {
	m_tool = NONE;
	m_widgets.toolIcons.Add("brush", sf::Vector2f(20, 20), sf::Vector2f(20, 20), "icons.png", sf::IntRect(0, 0, 20, 20),
		sf::IntRect(0, 20, 20, 20), sf::IntRect(0, 40, 20, 20));

	m_widgets.toolIcons.Add("pen", sf::Vector2f(20, 20), sf::Vector2f(50, 20), "icons.png", sf::IntRect(40, 0, 20, 20),
		sf::IntRect(40, 20, 20, 20), sf::IntRect(40, 40, 20, 20));

	m_widgets.toolIcons.Add("eraser", sf::Vector2f(20, 20), sf::Vector2f(80, 20), "icons.png", sf::IntRect(20, 0, 20, 20),
		sf::IntRect(20, 20, 20, 20), sf::IntRect(20, 40, 20, 20));
}

inline void Paint::init_colorIcons() {
	for (unsigned int i = 0; i < 8; i++) {
		if (i < 4) {
			m_widgets.colorIcons.Add(m_colorsNames[i], sf::Vector2f(20, 20), sf::Vector2f(900 + i * 30, 20), "ColorIcons.png", sf::IntRect(i * 20, 0, 20, 20),
				sf::IntRect(i * 20, 20, 20, 20), sf::IntRect(i * 20, 40, 20, 20));
		}
		else {
			m_widgets.colorIcons.Add(m_colorsNames[i], sf::Vector2f(20, 20), sf::Vector2f(900 + (i - 4) * 30, 50), "ColorIcons.png", sf::IntRect(i * 20, 0, 20, 20),
				sf::IntRect(i * 20, 20, 20, 20), sf::IntRect(i * 20, 40, 20, 20));
		}
	}
}

inline void Paint::init_tweakIcons() {
	m_widgets.tweakIcons.Add("colorPicker", sf::Vector2f(50, 55), sf::Vector2f(900 + (8 - 4) * 30, 20), "colorEditor.png", sf::IntRect(4, 5, 307, 309),
		sf::IntRect(6, 7, 305, 307), sf::IntRect(8, 9, 303, 305));
}

inline void Paint::init_pointers() {
	
}

inline void Paint::init_randomStuff() {
	m_currentColorDisplay.setPosition(835, 20);
	m_currentColorDisplay.setSize(sf::Vector2f(50, 55));
	m_currentColorDisplay.setFillColor(sf::Color::Black);

	m_brushSlider.AddSlider(sf::Vector2f(120, 30), 10, 200, 35);

	m_colorWheel.rect.setSize(sf::Vector2f(367, 368));
	m_colorWheel.rect.setPosition(225, 60);
	m_colorWheel.img.loadFromFile("./assets/color_wheel.png");
	m_colorWheel.tex.loadFromImage(m_colorWheel.img);
	m_colorWheel.rect.setTexture(&m_colorWheel.tex);
}

// end_inits --------------------------------------


// re-usables -------------------------------------------------------------------------------------------------------------------

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

void Paint::RunWindow(sf::RenderWindow& window, sf::Vector2u windowSize, std::string title, void(Paint::*run)()) {
	window.create(sf::VideoMode(windowSize.x, windowSize.y), title);
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

inline void Paint::SetBgColor(const sf::Color& color) {
	m_data->canvas->create(m_data->canvas_bounds.width, m_data->canvas_bounds.height, color);
}

// end_re-usables ---------------------------------------------------------------------------------------------------------------


// per-frame-functions -------------------------------------

inline void Paint::Clear() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		SetBgColor(m_data->backroundColor);
	}
}

void Paint::SelectClickedColor() {
	for (unsigned int i = 0; i < 8; i++) {
		if (m_widgets.colorIcons.Get(m_colorsNames[i]).IsClicked()) {
			m_colorPicked = false;
			m_selectedColor = (Colors)i;
		}
	}
	if (!m_colorPicked) {
		ChangeColor();
	}
}

void Paint::SelectClickedTools() {
	if (m_widgets.toolIcons.Get("pen").IsClicked()) {
		m_tool = PEN;
	}
	else if (m_widgets.toolIcons.Get("brush").IsClicked()) {
		m_tool = BRUSH;
	}
	else if (m_widgets.toolIcons.Get("eraser").IsClicked()) {
		m_tool = ERASER;
	}
	else {
		m_tool = NONE;
	}
}

void Paint::ChangeColor() {
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
	}
}

void Paint::LaunchWindows() {
	if (m_widgets.tweakIcons.Get("colorPicker").IsClicked()) {
		m_isColorSet = false;
		this->RunWindow(m_windows.colorPickerWindow, sf::Vector2u(600, 500), "Color Picker", &Paint::ColorPickerWindow);
	}
}

void Paint::PaintStuff() {
	switch (m_tool) {
	case BRUSH:
		Draw(m_windows.mainWindow, m_data->canvas_bounds, m_brushSlider.GetValue(), m_brushSlider.GetValue(), m_paintColor);
		break;
	case PEN:
		Draw(m_windows.mainWindow, m_data->canvas_bounds, m_brushSlider.GetValue() / 2, m_brushSlider.GetValue(), m_paintColor);
		break;
	case ERASER:
		Draw(m_windows.mainWindow, m_data->canvas_bounds, m_brushSlider.GetValue(), m_brushSlider.GetValue(), m_data->backroundColor);
		break;
	default:
		break;
	}
}

inline void Paint::UpdateColorDisplay() {
	m_currentColorDisplay.setPosition(835, 20);
	m_currentColorDisplay.setSize(sf::Vector2f(50, 55));
	m_currentColorDisplay.setFillColor(m_paintColor);
	m_windows.mainWindow.draw(m_currentColorDisplay);
}

void Paint::SetPointer() {
	
}

// end_per-frame-functions ---------------------------------


void Paint::ColorPickerWindow() {
	if (!m_isColorSet) {
		m_pixelColor = m_paintColor;
		m_isColorSet = true;
	}
	m_windows.colorPickerWindow.clear(sf::Color::White);
	m_windows.colorPickerWindow.draw(m_colorWheel.rect);
	m_Ok_cancel_cp.Update(m_windows.colorPickerWindow);

	m_currentColorDisplay.setSize(sf::Vector2f(180, 150));
	m_currentColorDisplay.setPosition(25, 90);
	m_windows.colorPickerWindow.draw(m_currentColorDisplay);

	int x = m_colorWheel.rect.getPosition().x;
	int y = m_colorWheel.rect.getPosition().y;
	int w = x + m_colorWheel.rect.getGlobalBounds().width;
	int h = y + m_colorWheel.rect.getGlobalBounds().height;

	m_cpRGB.setRGB(m_currentColorDisplay.getFillColor());
	m_cpRGB.rgb.setPosition(65, 250);
	m_windows.colorPickerWindow.draw(m_cpRGB.rgb);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Interface::IsMouseInBounds(m_windows.colorPickerWindow, sf::IntRect(x, y, w, h))) {
		m_pixelColor = m_colorWheel.img.getPixel(sf::Mouse::getPosition(m_windows.colorPickerWindow).x - x, sf::Mouse::getPosition(m_windows.colorPickerWindow).y - y);
		m_currentColorDisplay.setFillColor(m_pixelColor);
	}
	if (m_Ok_cancel_cp.ok_cancel.Get("ok").IsClicked()) {
		m_widgets.colorIcons.DeselectAll();
		m_colorPicked = true;
		m_paintColor = m_pixelColor;
		m_windows.colorPickerWindow.close();
	}
	if (m_Ok_cancel_cp.ok_cancel.Get("cancel").IsClicked()) {
		m_windows.colorPickerWindow.close();
	}
}

void Paint::ToolSizeWindow() {

}


// publically-used ---------------------------------

void Paint::Initialize(Data* data) {
	m_data          = data;
	m_tool          = NONE;
	m_selectedColor = BLACK;
	m_paintColor    = sf::Color::Black;

	init_toolIcons();
	init_colorIcons();
	init_tweakIcons();
	init_pointers();

	init_randomStuff();
}

void Paint::Run() {
	Clear();
	m_widgets.tweakIcons.Update(m_windows.mainWindow);
	m_widgets.toolIcons.Update(m_windows.mainWindow);
	m_widgets.colorIcons.Update(m_windows.mainWindow);
	SelectClickedColor();
	SelectClickedTools();
	LaunchWindows();
	PaintStuff();
	UpdateColorDisplay();
	SetPointer();
}

// end_publically-used -----------------------------


Paint::~Paint() {
	
}