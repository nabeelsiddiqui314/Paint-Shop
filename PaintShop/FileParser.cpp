#include "stdafx.h"
#include "FileParser.h"


FileParser::FileParser() :
	m_data_filepath("./Data/save_data.txt")
{
}


bool FileParser::Parse(Data* data) {
	m_data = data;
	if (!m_data) {
		return false;
	}
	if (!OpenFiles()) {
		return false;
	}

	return true;
}

bool FileParser::OpenFiles() {
	m_read_data.open(m_data_filepath);
	if (!m_read_data.is_open()) {
		PrintError("cannot open file");
		return false;
	}

	std::string temp;

	while (std::getline(m_read_data, temp)) {
		if (temp == "SIZE") {
			m_read_data >> temp;
			m_data->window_size.x = std::stoi(temp, nullptr);
			m_read_data >> temp;
			m_data->window_size.y = std::stoi(temp, nullptr);
		}
		else if (temp == "BG-COLOR") {
			m_read_data >> temp;
			int r = std::stoi(temp, nullptr);
			m_read_data >> temp;
			int g = std::stoi(temp, nullptr);
			m_read_data >> temp;
			int b = std::stoi(temp, nullptr);

			m_data->backroundColor = sf::Color(r, g, b);
		}
	}

	return true;
}

void FileParser::Write() {
	m_write_data.open(m_data_filepath);

	m_write_data.clear();
	m_write_data << "SIZE\n"
		<< m_data->window_size.x << " " << m_data->window_size.y << "\n"
		<< "BG-COLOR\n"
		<< (int)m_data->backroundColor.r << " " << (int)m_data->backroundColor.g << " " << (int)m_data->backroundColor.b;
}

void FileParser::PrintError(std::string errorMessage) {
	std::cerr << "[ERROR]: " << errorMessage << std::endl;
}


FileParser::~FileParser()
{
}
