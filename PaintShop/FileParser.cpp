#include "stdafx.h"
#include "FileParser.h"


FileParser::FileParser() :
	m_windowSize_filepath("Data/window_size.txt")
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
	m_read_window_size.open(m_windowSize_filepath);
	if (!m_read_window_size.is_open()) {
		PrintError("cannot open file");
		return false;
	}

	std::string temp;

	m_read_window_size >> m_data->window_size.x >> m_data->window_size.y;

	return true;
}

void FileParser::Write() {
	m_write_window_size.open(m_windowSize_filepath);

	m_write_window_size.clear();
	m_write_window_size << m_data->window_size.x << " " << m_data->window_size.y;
}

void FileParser::PrintError(std::string errorMessage) {
	std::cerr << "[ERROR]: " << errorMessage << std::endl;
}


FileParser::~FileParser()
{
}
