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
#include <SFML/System/Time.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"


class thread_vision
{

public:
	void operator()(int index);

private:

	//filter for continue button
	cv::Mat button_filter();

	//filter for tapes under the boxes
	cv::Mat box_filters();

	//filter to checking if wrong boxes detected
	cv::Mat Other_box_filters(int i);

	//pomocnicza funkcja do usuniecia
	void display_Tracksbars(int &hmin, int &hmax, int &smin, int &smax, int &vmin, int &vmax);

	//nieuzywana sprawdza dwa prostokaty i liczy roznice
	bool check_pattern_two_rect(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);

	//checking if green button is visible
	bool check_pattern_circle(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);

	//checking if rectangle is visible
	bool check_pattern_one_rect(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);

	//checking boxes in configuration table section
	bool check_if_boxes_on_position(cv::Mat input_image, int index);

	//initialization box places
	void init_boxes();

	//initialization tape places 
	void init_tape_places();

	//calculating mean thresh on the tapes
	int calc_mean_thresh();

	//vector of points // calibration section
	std::vector<cv::Point> image_calibration(cv::VideoCapture cam);
	std::vector<cv::Point> find_contours_for_calib(cv::Mat mask);
	std::vector<cv::Point> reorder(std::vector<cv::Point> points);

	//one time setting params
	void set_warp_parameters(float w, float h);

	//saved image from camera;
	cv::Mat image;
	cv::Mat box;

	//variables to communication
	bool green_button;
	bool box_detection;

	//vectors of rects to cropping images
	std::vector <cv::Rect> boxes;
	std::vector <cv::Rect> tapes;
	cv::Point TL_of_window;

	// Pomocnicze zmienne do ustalania tresholdu
	int tresh_min = 0;
	int tresh_max = 255;

	bool is_sequence_activated;

	//control time between steps of sequence
	sf::Time time_compare = sf::seconds(3);
	sf::Time real_time;
	sf::Clock clock;

	//if taking article detected
	bool box_flag;

	//if calibration section
	bool calibration_flag;

	//points to do square image
	std::vector<cv::Point>coordinates_reordered;
	cv::Mat transformation_x, transformation_y; // Matrix x and y are used for warping image

	//variable used in configuration boxes section
	std::vector<std::pair<int, int>> previous_info_accepted_boxes;

	//Article taking or article installing
	int current_step;

	//if wrong article taken
	bool wrong;

	//if calibration boxes section is active
	bool calibration_boxes;

	//icrementators of any objects // if detected obejects then ++
	int green_inc;
	int box_inc;
	int wrong_box_inc;
	int setting_boxes_inc[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int previous_wrong_box_inc;

	int amount_of_loops_to_change_state = 4;

};



#endif // !VISION_H