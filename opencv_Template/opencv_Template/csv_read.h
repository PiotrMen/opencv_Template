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

void load_csv_database(std::vector <sData> &articles_in_boxes, std::vector <sData> &left_articles);
void save_csv_database(const std::vector <sData> &articles_in_boxes, const std::vector <sData> &left_articles);

#endif // !CSV_READ_H