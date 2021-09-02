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

	cv::Mat button_filters();
	cv::Mat button_filter();
	cv::Mat box_filters();
	cv::Mat Other_box_filters(int i);
	void display_Tracksbars(int &hmin, int &hmax, int &smin, int &smax, int &vmin, int &vmax);
	bool check_pattern(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);
	bool check_pattern_circle(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);
	bool check_pattern_one_rect(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value);
	bool check_if_boxes_on_position(cv::Mat input_image, int index);
	void init_boxes();
	void init_tape_places();
	int calc_mean_thresh();
	std::vector<cv::Point> image_calibration(cv::VideoCapture cam);
	std::vector<cv::Point> find_contours_for_calib(cv::Mat mask);
	std::vector<cv::Point> reorder(std::vector<cv::Point> points);
	cv::Mat getWarp(cv::Mat img, std::vector<cv::Point> points, float w, float h);
	void set_warp_parameters(float w, float h);

	cv::Mat image;
	cv::Mat trackbars_img;
	cv::Mat box;

	bool green_button;
	bool box_detection;

	std::vector <cv::Rect> boxes;
	std::vector <cv::Rect> tapes;
	cv::Point TL_of_window;

	// Pomocnicze zmienne do ustalania tresholdu
	int tresh_min = 0;
	int tresh_max = 255;

	bool is_sequence_activated = false;

	sf::Time time_compare = sf::seconds(3);
	sf::Time time_calibration_camera = sf::seconds(30);

	sf::Time real_time;
	sf::Clock clock;

	bool box_flag;
	bool calibration_flag;

	std::vector<cv::Point>coordinates_reordered;
	cv::Mat transformation_x, transformation_y; // Matrix x and y are used for warping image

	std::vector<std::pair<int, int>> previous_info_accepted_boxes;

	int current_step;
	bool wrong;

	bool calibration_boxes;

	int green_inc;
	int box_inc;
	int wrong_box_inc;
	int setting_boxes_inc[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int previous_wrong_box_inc;
	bool any_wrong_boxes_detected;

	int amount_of_loops_to_change_state = 4;

	int threshold_from_file;
};



#endif // !VISION_H