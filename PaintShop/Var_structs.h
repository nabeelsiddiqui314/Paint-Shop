#pragma once
#include "Widget.h"
#include "WidgetManager.h"
#include "Slider.h"
#include <string>
#include <vector>

struct Windows {
	sf::RenderWindow& mainWindow;
	sf::RenderWindow  colorPickerWindow;
	sf::RenderWindow  toolSizeWindow;
	Windows(sf::RenderWindow& window) : mainWindow(window) {}
};

struct WidgetGroups {
	WidgetManager toolIcons = WidgetManager(SELECT);
	WidgetManager colorIcons = WidgetManager(SELECT);
	WidgetManager tweakIcons = WidgetManager(INFINITE);
};

struct RGB {
	sf::Font font;
	sf::Text rgb;

	RGB() {
		font.loadFromFile("./assets/font.ttf");
		rgb.setFont(font);
		rgb.setCharacterSize(18);
		rgb.setFillColor(sf::Color::Black);
	}
	void setRGB(const sf::Color& color) {
		rgb.setString("RGB: " + std::to_string((int)color.r) + ", " + std::to_string((int)color.g) + ", " + std::to_string((int)color.b));
	}
};

struct ColorWheel {
	sf::RectangleShape rect;
	sf::Texture        tex;
	sf::Image          img;
};

struct Ok_Cancel {
	WidgetManager ok_cancel = WidgetManager(INFINITE);
	Ok_Cancel(sf::Vector2f PosOk, sf::Vector2f PosCancel) {
		ok_cancel.Add("ok",     sf::Vector2f(50, 20), PosOk,     "ok_cancel.png", sf::IntRect(  0, 0, 104, 40), sf::IntRect(  0, 45, 102, 38), sf::IntRect(  0, 45, 102, 38));
		ok_cancel.Add("cancel", sf::Vector2f(50, 20), PosCancel, "ok_cancel.png", sf::IntRect(126, 0, 104, 40), sf::IntRect(126, 45, 102, 38), sf::IntRect(126, 45, 102, 38));
	}
	void Update(sf::RenderWindow& window) {
		ok_cancel.Update(window);
	}
};