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

	void display_Tracksbars(int &hmin, int &hmax, int &smin, int &smax, int &vmin, int &vmax);
	bool Is_button_covered(int select_button);
	cv::Mat image;
	cv::Mat trackbars_img;
};



#endif // !VISION_H