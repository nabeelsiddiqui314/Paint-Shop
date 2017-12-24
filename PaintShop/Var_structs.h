#pragma once
#include "WidgetManager.h"
#include "Slider.h"
#include <string>
#include <vector>

struct Windows {
	sf::RenderWindow& mainWindow;
	sf::RenderWindow  colorPickerWindow;
	sf::RenderWindow  toolSizeWindow;
	sf::RenderWindow  saveImg;
	Windows(sf::RenderWindow& window) : mainWindow(window) {}
};

struct WidgetGroups {
	WidgetManager toolIcons = WidgetManager(SELECT);
	WidgetManager colorIcons = WidgetManager(SELECT);
	WidgetManager tweakIcons = WidgetManager(INFINITE);
	WidgetManager saveIcon = WidgetManager(INFINITE);
};

struct FormalText : public sf::Text {
	FormalText() {
		font.loadFromFile("./assets/fonts/openSans.ttf");
		this->setFont(font);
	}
private:
	sf::Font font;
};

struct FancyText : public sf::Text {
	FancyText() {
		font.loadFromFile("./assets/fonts/fancy.ttf");
		this->setFont(font);
	}
private:
	sf::Font font;
};

struct RGB {
	FancyText rgb;

	RGB() {
		rgb.setCharacterSize(18);
		rgb.setFillColor(sf::Color::Black);
	}
	void setRGB(const sf::Color& color) {
		rgb.setString("RGB: " + std::to_string((int)color.r) + ", " + std::to_string((int)color.g) + ", " + std::to_string((int)color.b));
	}
};

struct Rect {
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

struct InfoBar {
	sf::RectangleShape bar;
	FancyText canvasSize;
	FancyText mousePos;
	sf::RenderWindow* window;
};

struct BoolSwitches {
	bool isColorSet = false;
	bool colorPicked = false;
	bool isPointerSet = false;
	bool isPointerSetCP = false;
};