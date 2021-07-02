#pragma once
#ifndef CSV_READ_H
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <regex>
#include <fstream>
#include <iomanip>
#include <regex>


struct sData
{
	int serial_number;
	std::string name;

};

void load_data(std::vector <sData> &articles);

#endif // !CSV_READ_H