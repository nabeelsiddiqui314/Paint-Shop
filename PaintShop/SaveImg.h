#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Data.h"

class SaveImg
{
public:
	 SaveImg();
	~SaveImg();
public:
	void InitData(Data* data);
	void Save();
private:
	void SetNewImgNumber();
private:
	Data* m_data;
};

