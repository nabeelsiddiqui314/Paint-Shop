#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Data.h"
#include "Interface.h"
#include "Var_structs.h"
#include "PointerManager.h"
#include "SaveImg.h"

enum Tool {
	NONE,
	PEN,
	BRUSH,
	ERASER,
	FILL_BUCKET
};

enum Colors {
	BLACK,
	WHITE,
	BLUE,
	RED,
	GREEN,
	PINK,
	CYAN,
	YELLOW
};

class Paint
{
public:
	 Paint(sf::RenderWindow& window);
	~Paint();
public:
	void Initialize (Data* data);
	void Run();
private:
	inline void init_toolIcons();
	inline void init_colorIcons();
	inline void init_tweakIcons();
	inline void init_pointers();
	inline void init_randomStuff();
	inline void init_infoBar();

	void Draw(sf::RenderWindow& window, const sf::IntRect& bounds, int width, int height, const sf::Color& color);
	void RunWindow(sf::RenderWindow& window, sf::Vector2u windowSize, std::string title, void(Paint::*run)());
	inline void SetBgColor(const sf::Color& color);

	inline void Clear();
	void SelectClickedColor();
	void SelectClickedTools();
	void ChangeColor();
	void LaunchWindows();
	void PaintStuff();
	inline void UpdateColorDisplay();
	void SetPointer();
	void UpdateInfoBar();

	void ColorPickerWindow();
	void SaveWindow();
private:
	Data*              m_data;
	Tool               m_tool;
	
	Colors              m_selectedColor;
	sf::Color           m_paintColor;
	sf::Color           m_pixelColor;

	Slider              m_brushSlider;
	sf::RectangleShape  m_currentColorDisplay;
	PointerManager      m_pointers;

	Windows      m_windows;
	WidgetGroups m_widgets;
	RGB          m_cpRGB;
	Rect         m_colorWheel;
	Ok_Cancel    m_Ok_cancel_cp;
	InfoBar      m_infoBar;
	BoolSwitches m_boolSwitches;
	Ok_Cancel    m_Ok_cancel_save;
	SaveImg      m_img;
	Rect         m_preview;
	FormalText   m_saveMsg;

	std::string   m_colorsNames[8] = { 
		"BLACK",
		"WHITE",
		"BLUE",
		"RED",
		"GREEN",
		"PINK",
		"CYAN",
		"YELLOW",
	};
};