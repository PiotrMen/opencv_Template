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

	int quantity;
	float width;
	float height;

	int matched_rectangle;
	bool wrong_number = false;
	bool repeated_number = false;
};

struct sGlobal_data
{
	bool is_sequence_activated;

	bool green_button;
	bool red_button;
	bool detecting_box;
	float measurement;

	std::vector<sf::RectangleShape> boxes;

	int current_step = 0;
};



void load_csv_database(std::vector <sData> &articles_in_boxes, std::vector <sData> &left_articles);
void save_csv_database(const std::vector <sData> &articles_in_boxes, const std::vector <sData> &left_articles);

void load_csv_sequence(std::vector <sData> &sequence, std::string file_name, std::vector <sData> &connectors_list);
void generate_connectors_list(const std::vector <sData> &sequence, std::vector <sData> &connectors_list);

std::string load_txt_help(std::string filename);

#endif // !CSV_READ_H