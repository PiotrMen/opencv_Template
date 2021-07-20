#pragma once
#ifndef VISION_H
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "Universal_functions.h"


class thread_vision
{

public:
	void operator()(int index);

private:

	cv::Mat button_filters(int select_button);
	cv::Mat box_filters();
	void display_Tracksbars(int &hmin, int &hmax, int &smin, int &smax, int &vmin, int &vmax);
	bool check_pattern(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);
	bool check_pattern_one_rect(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);
	void init_boxes();

	cv::Mat image;
	cv::Mat trackbars_img;

	bool green_button;
	bool red_button;
	bool box_detection;

	std::vector <cv::Rect> boxes;
	cv::Point TL_of_window;

	// Pomocnicze zmienne do ustalania tresholdu
	int tresh_min = 0;
	int tresh_max = 255;

	bool is_sequence_activated = false;
};



#endif // !VISION_H