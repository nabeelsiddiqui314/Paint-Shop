#include "stdafx.h"
#include "Paint.h"


Paint::Paint(sf::RenderWindow& window) : 
	m_windows (window),
	m_Ok_cancel_cp(sf::Vector2f(50, 450), sf::Vector2f(150, 450)),
	m_Ok_cancel_save(sf::Vector2f(350, 450), sf::Vector2f(450, 450))
{
	
}


// inits ------------------------------------------

inline void Paint::init_toolIcons() {
	m_tool = NONE;
	m_widgets.toolIcons.Add("brush", sf::Vector2f(20, 20), sf::Vector2f(80, 20), "icons.png", sf::IntRect(0, 0, 20, 20),
		sf::IntRect(0, 20, 20, 20), sf::IntRect(0, 40, 20, 20));

	m_widgets.toolIcons.Add("pen", sf::Vector2f(20, 20), sf::Vector2f(110, 20), "icons.png", sf::IntRect(40, 0, 20, 20),
		sf::IntRect(40, 20, 20, 20), sf::IntRect(40, 40, 20, 20));

	m_widgets.toolIcons.Add("eraser", sf::Vector2f(20, 20), sf::Vector2f(140, 20), "icons.png", sf::IntRect(20, 0, 20, 20),
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
	m_widgets.tweakIcons.Add("colorPicker", sf::Vector2f(50, 50), sf::Vector2f(900 + (8 - 4) * 30, 20), "colorEditor.png", sf::IntRect(4, 5, 307, 309),
		sf::IntRect(6, 7, 305, 307), sf::IntRect(8, 9, 303, 305));
}

inline void Paint::init_pointers() {
	m_pointers.Add("brush", "brush.png", sf::Vector2f(40, 40), sf::Vector2f(2, 37));
	m_pointers.Add("pen", "pen.png", sf::Vector2f(40, 40), sf::Vector2f(1, 39));
	m_pointers.Add("eraser", "eraser.png", sf::Vector2f(40, 40), sf::Vector2f(20, 20));
	m_pointers.Add("colorPicker", "color_picker.png", sf::Vector2f(40, 40), sf::Vector2f(3, 37));
}

inline void Paint::init_randomStuff() {
	m_currentColorDisplay.setPosition(835, 20);
	m_currentColorDisplay.setSize(sf::Vector2f(50, 50));
	m_currentColorDisplay.setFillColor(sf::Color::Black);

	m_brushSlider.AddSlider(sf::Vector2f(400, 30), 10, 200, 35);

	m_colorWheel.rect.setSize(sf::Vector2f(367, 368));
	m_colorWheel.rect.setPosition(225, 60);
	m_colorWheel.img.loadFromFile("./assets/color_wheel.png");
	m_colorWheel.tex.loadFromImage(m_colorWheel.img);
	m_colorWheel.rect.setTexture(&m_colorWheel.tex);

	m_preview.rect.setPosition(70, 100);
	m_preview.rect.setSize(sf::Vector2f(450, 250));

	m_saveMsg.setCharacterSize(15);
	m_saveMsg.setPosition(70, 50);
	m_saveMsg.setFillColor(sf::Color::Black);
}

inline void Paint::init_infoBar() {
	m_infoBar.bar.setPosition(0, m_windows.mainWindow.getSize().y - 20);
	m_infoBar.bar.setSize(sf::Vector2f(m_windows.mainWindow.getSize().x, 20));
	m_infoBar.bar.setFillColor(sf::Color(226, 227, 255));
	m_infoBar.canvasSize.setFillColor(sf::Color::Black);
	m_infoBar.mousePos.setFillColor(sf::Color::Black);
	m_infoBar.canvasSize.setCharacterSize(12);
	m_infoBar.mousePos.setCharacterSize(12);
	m_infoBar.mousePos.setPosition(50, m_windows.mainWindow.getSize().y - 15);
	m_infoBar.canvasSize.setPosition(950, m_windows.mainWindow.getSize().y - 15);
}

// end_inits --------------------------------------


// re-usables -------------------------------------------------------------------------------------------------------------------

void Paint::Draw(sf::RenderWindow& window, const sf::IntRect& bounds, int width, int height, const sf::Color& color) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Interface::IsMouseInBounds(window, bounds)) {
		for (int x = sf::Mouse::getPosition(window).x - width; x < sf::Mouse::getPosition(window).x + width; x++) {
			for (int y = sf::Mouse::getPosition(window).y - height; y < sf::Mouse::getPosition(window).y + height; y++) {
				if (x - m_data->canvas_bounds.left > m_data->canvas_bounds.width - 1 || x - m_data->canvas_bounds.left < 0 ||
					y - m_data->canvas_bounds.top > m_data->canvas_bounds.height - 1 || y - m_data->canvas_bounds.top < 0) {

				}
				else {
					m_data->canvas->setPixel(x - m_data->canvas_bounds.left, y - m_data->canvas_bounds.top, color);
				}
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
			m_boolSwitches.colorPicked = false;
			m_selectedColor = (Colors)i;
		}
	}
	if (!m_boolSwitches.colorPicked) {
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
		m_boolSwitches.isColorSet = false;
		this->RunWindow(m_windows.colorPickerWindow, sf::Vector2u(600, 500), "Color Picker", &Paint::ColorPickerWindow);
	}
	if (m_widgets.saveIcon.Get("save").IsClicked()) {
		m_preview.tex.loadFromImage(*m_data->canvas);
		m_preview.rect.setTexture(&m_preview.tex);
		m_saveMsg.setString("Save as: img" + std::to_string(m_data->img_number) + ".png");
		this->RunWindow(m_windows.saveImg, sf::Vector2u(600, 500), "Save", &Paint::SaveWindow);
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
	m_currentColorDisplay.setSize(sf::Vector2f(50, 50));
	m_currentColorDisplay.setFillColor(m_paintColor);
	m_windows.mainWindow.draw(m_currentColorDisplay);
}

void Paint::SetPointer() {
	if (Interface::IsMouseInBounds(m_windows.mainWindow, sf::IntRect(m_data->canvas_bounds))) {
		if (!m_boolSwitches.isPointerSet) {
			if (m_widgets.toolIcons.Get("brush").IsClicked()) {
				m_pointers.SetPointer("brush");
			}
			else if (m_widgets.toolIcons.Get("pen").IsClicked()) {
				m_pointers.SetPointer("pen");
			}
			else if (m_widgets.toolIcons.Get("eraser").IsClicked()) {
				m_pointers.SetPointer("eraser");
			}
			else {
				m_pointers.DontDisplay();
			}
			m_boolSwitches.isPointerSet = true;
		}
	}
	else {
		m_boolSwitches.isPointerSet = false;
		m_pointers.DontDisplay();
	}
}

void Paint::UpdateInfoBar() {
	m_infoBar.canvasSize.setString("Canvas Size: " + std::to_string(m_data->canvas_bounds.width) + " x " + std::to_string(m_data->canvas_bounds.height));
	if (Interface::IsMouseInBounds(m_windows.mainWindow, m_data->canvas_bounds)) {
		sf::Vector2i Pos = { sf::Mouse::getPosition(m_windows.mainWindow).x - m_data->canvas_bounds.left, sf::Mouse::getPosition(m_windows.mainWindow).y - m_data->canvas_bounds.top };
		m_infoBar.mousePos.setString("Position: " + std::to_string(Pos.x) + " x " + std::to_string(Pos.y));
	}
	else {
		m_infoBar.mousePos.setString("Position: Outside Canvas");
	}
	m_windows.mainWindow.draw(m_infoBar.bar);
	m_windows.mainWindow.draw(m_infoBar.canvasSize);
	m_windows.mainWindow.draw(m_infoBar.mousePos);
}

// end_per-frame-functions ---------------------------------


void Paint::ColorPickerWindow() {
	if (!m_boolSwitches.isColorSet) {
		m_pixelColor = m_paintColor;
		m_boolSwitches.isColorSet = true;
	}
	m_windows.colorPickerWindow.clear(sf::Color::White);
	m_windows.colorPickerWindow.draw(m_colorWheel.rect);
	m_Ok_cancel_cp.Update(m_windows.colorPickerWindow);

	m_currentColorDisplay.setSize(sf::Vector2f(180, 150));
	m_currentColorDisplay.setPosition(25, 90);
	m_windows.colorPickerWindow.draw(m_currentColorDisplay);

	int x = m_colorWheel.rect.getPosition().x;
	int y = m_colorWheel.rect.getPosition().y;
	int w = m_colorWheel.rect.getGlobalBounds().width;
	int h = m_colorWheel.rect.getGlobalBounds().height;

	if (Interface::IsMouseInBounds(m_windows.colorPickerWindow, sf::IntRect(x, y, w, h))) {
		if (!m_boolSwitches.isPointerSetCP) {
			m_pointers.SetPointer("colorPicker");
			m_boolSwitches.isPointerSetCP = true;
		}
	}
	else {
		m_boolSwitches.isPointerSetCP = false;
		m_pointers.DontDisplay();
	}

	m_pointers.Update(m_windows.colorPickerWindow);
	m_cpRGB.setRGB(m_currentColorDisplay.getFillColor());
	m_cpRGB.rgb.setPosition(65, 250);
	m_windows.colorPickerWindow.draw(m_cpRGB.rgb);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Interface::IsMouseInBounds(m_windows.colorPickerWindow, sf::IntRect(x, y, w-1, h-1))) {
		m_pixelColor = m_colorWheel.img.getPixel(sf::Mouse::getPosition(m_windows.colorPickerWindow).x - x, sf::Mouse::getPosition(m_windows.colorPickerWindow).y - y);
		m_currentColorDisplay.setFillColor(m_pixelColor);
	}
	
	if (m_Ok_cancel_cp.ok_cancel.Get("ok").IsClicked()) {
		m_widgets.colorIcons.DeselectAll();
		m_boolSwitches.colorPicked = true;
		m_paintColor = m_pixelColor;
		m_windows.colorPickerWindow.close();
	}
	if (m_Ok_cancel_cp.ok_cancel.Get("cancel").IsClicked()) {
		m_windows.colorPickerWindow.close();
	}
}

void Paint::SaveWindow() {
	m_windows.saveImg.clear(sf::Color(222, 227, 255));
	m_Ok_cancel_save.Update(m_windows.saveImg);

	m_windows.saveImg.draw(m_preview.rect);
	m_windows.saveImg.draw(m_saveMsg);

	if (m_Ok_cancel_save.ok_cancel.Get("ok").IsClicked()) {
		m_img.Save();
		m_windows.saveImg.close();
	}
	if (m_Ok_cancel_save.ok_cancel.Get("cancel").IsClicked()) {
		m_windows.saveImg.close();
	}
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
	init_infoBar();

	init_randomStuff();
	m_img.InitData(m_data);
	m_widgets.saveIcon.Add("save", sf::Vector2f(25, 25), sf::Vector2f(5, 5), "saveIcon.png", sf::IntRect(0, 0, 25, 25), sf::IntRect(0, 25, 25, 25), sf::IntRect(0, 50, 25, 25));
}

void Paint::Run() {
	Clear();
	m_widgets.tweakIcons.Update(m_windows.mainWindow);
	m_widgets.toolIcons.Update(m_windows.mainWindow);
	m_widgets.colorIcons.Update(m_windows.mainWindow);
	m_widgets.saveIcon.Update(m_windows.mainWindow);
	m_brushSlider.Update(m_windows.mainWindow);
	m_pointers.Update(m_windows.mainWindow);
	UpdateInfoBar();
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