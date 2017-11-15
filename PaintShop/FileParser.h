#pragma once
#include "Data.h"
#include <iostream>
#include <fstream>
#include <sstream>

class FileParser
{
public:
	 FileParser();
	~FileParser();
public:
	bool Parse(Data* data); // this will be called in constructor
	void Write(); // this will be called before program ends
private:
	bool          OpenFiles();
	void          PrintError(std::string errorMessage);
	std::ifstream m_read_data;
	std::ofstream m_write_data;
	Data*         m_data;
	std::string   m_data_filepath;
};

