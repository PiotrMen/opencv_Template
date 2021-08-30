#pragma once
#ifndef LIVE_CHART_H
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "opencv2/opencv.hpp"
#include <regex>
#include <fstream>
#include <iomanip>

class cLive_chart
{
public:
	// Times represented on chart
	float max_sequence_time;
	float min_sequence_time;
	std::vector<float> sequence_times;

	int oldest_time_recorded_iterator;

	float time_mean_value;

public:

	// Loading and saving statistics in csv file
	void load_statistics();
	void save_statistics();
	
	// Ads new time to the csv file after sequence is over
	void add_new_time(float new_time);
};


#endif // !LIVE_CHART_H