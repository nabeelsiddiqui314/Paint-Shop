#pragma once
#include "Widget.h"
#include "WidgetManager.h"
#include "Slider.h"
#include <string>

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