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

public:

	// Loading and saving statistics in csv file
	void load_statistics();
	void save_statistics();
};


#endif // !LIVE_CHART_H