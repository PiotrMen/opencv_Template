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
#include "Universal_functions.h"

class cLive_chart
{
private:

	bool detecting_rising_edge(bool signal);
	bool detecting_falling_edge(bool signal);
	bool detecting_rising_edge_left_mouse_button();
	bool detecting_falling_edge_left_mouse_button();
	void Live_chart_axis_display(std::string file_path,sf::RenderWindow *window);
	void Live_chart_bars_display(int pos_x, int pos_y, std::string file_path, sf::RenderWindow *window);

	//Position in pixels and size of Live Chart
	int pos_x;
	int pos_y;
	int size;
	float scale;
	int image_size;
	float coefficient;
	float first_bar;
	float second_bar;
	float third_bar;
	float fourth_bar;

	// Times represented on chart
	float max_sequence_time;
	float min_sequence_time;
	std::vector<float> sequence_times;

	int previous_current_menu_window;
	int current_menu_window;

	//Edges
	bool rising_edge = false;
	bool rising_edge_detected = false;
	bool falling_edge = false;
	bool rising_edge_saved;
	bool falling_edge_detected = false;
	bool falling_edge_saved;

	//Edges_on_signal_trigger
	bool rising_edge_signal = false;
	bool rising_edge_detected_signal = false;
	bool falling_edge_signal = false;
	bool falling_edge_detected_signal = false;

	int oldest_time_recorded_iterator;

	float time_mean_value;
	float present_time = 0;

	// Chart bars

	sf::Sprite max_time_bar;
	sf::Sprite min_time_bar;
	sf::Sprite average_time_bar;
	sf::Sprite present_time_bar;

	//Timer

	sf::Clock sequence_clock;
	sf::Time time_of_sequence;

public:

	//Constructor
	cLive_chart(int pos_x, int pos_y, int size);

	bool if_active;
	// Loading and saving statistics in csv file
	void load_statistics();
	void save_statistics();

	void update(int &current_menu_window, bool &if_clear, bool &if_display, sf::RenderWindow *menu_window);
	void render(bool &if_clear, bool &if_display, sf::RenderWindow *menu_window);
	
	// Ads new time to the csv file after sequence is over
	void add_new_time(float new_time);

	// Calculating parameters of chart
	void calculating_bars();

};


#endif // !LIVE_CHART_H