#pragma once
#ifndef CSV_READ_H
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "opencv2/opencv.hpp"
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
	
	// Vision
	bool green_button;
	bool detecting_box;
	bool camera_calibration;
	bool global_exit;
	bool timer_done;
	bool wrong_box;

	bool last_step_of_sequence;

	bool calibration_box;

	sf::Time real_time_calibration_camera;

	std::vector<cv::Point> table_coordinates;

	std::vector<sf::RectangleShape> boxes;

	int step_in_sequence = 0;
	int current_step = 0;

	int connectors_list_size;

	bool step_back = false;					// true if user wants to go back to previous step in sequence
};



void load_csv_database(std::vector <sData> &articles_in_boxes, std::vector <sData> &left_articles);
void save_csv_database(const std::vector <sData> &articles_in_boxes, const std::vector <sData> &left_articles);

void load_csv_sequence(std::vector <sData> &sequence, std::string file_name, std::vector <sData> &connectors_list);
void generate_connectors_list(const std::vector <sData> &sequence, std::vector <sData> &connectors_list);

std::string load_txt_help(std::string filename);

void load_table_coordinates(std::vector <cv::Point> &points);
void save_table_coordinates(std::vector <cv::Point> points);

#endif // !CSV_READ_H