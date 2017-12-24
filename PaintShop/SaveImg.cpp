#include "stdafx.h"
#include "SaveImg.h"


SaveImg::SaveImg()
{
}


void SaveImg::InitData(Data* data) {
	m_data = data;
}

void SaveImg::Save() {
	m_data->canvas->saveToFile("./Images/" + std::to_string(m_data->img_number) + ".png");
	SetNewImgNumber();
}

void SaveImg::SetNewImgNumber() {
	m_data->img_number++;
}


SaveImg::~SaveImg()
{
}
