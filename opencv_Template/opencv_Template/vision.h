#pragma once
#ifndef VISION_H
#include <thread>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>

class thread_vision
{

public:
	void operator()(int index);

private:

	bool Is_button_covered(int select_button);
	void display_Tracksbars(int &hmin, int &hmax, int &smin, int &smax, int &vmin, int &vmax);
	bool check_pattern(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);

	cv::Mat image;
	cv::Mat trackbars_img;

	// Pomocnicze zmienne do ustalania tresholdu
	int tresh_min = 0;
	int tresh_max = 255;
};



#endif // !VISION_H