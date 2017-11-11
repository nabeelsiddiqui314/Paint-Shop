#include "stdafx.h"
#include "FileParser.h"


FileParser::FileParser()
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
	m_read_window_size.open("Data/window_size.txt");
	if (!m_read_window_size.is_open()) {
		PrintError("Inavlid filepath");
	}

	std::string temp;

	m_read_window_size >> m_data->window_size.x >> m_data->window_size.y;

	return true;
}

void FileParser::Write() {
	m_write_window_size.open("Data/window_size.txt");

	if (!m_write_window_size.is_open()) {
		PrintError("Inavlid filepath");
	}

	m_write_window_size.clear();
	m_write_window_size << m_data->window_size.x << " " << m_data->window_size.y;
}

void FileParser::PrintError(std::string errorMessage) {
	std::cerr << "[ERROR]: " << errorMessage << std::endl;
}


FileParser::~FileParser()
{
}
