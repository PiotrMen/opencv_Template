#pragma once
#ifndef WINDOW_FUNCTIONS__H
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "Universal_functions.h"



class sfml_objects
{
public:
	// green button

	// length of sides in pixels
	int green_button_length_x;
	int green_button_length_y;

	//coordinates
	int green_button_x;
	int green_button_y;

	// red button

	// length of sides in pixels
	int red_button_length_x;
	int red_button_length_y;

	//coordinates
	int red_button_x;
	int red_button_y;

	float button_size; //scaled button size (percentage)

	sf::RenderWindow *window;
	sf::Event event;
	//window size
	int window_width;
	int window_height;

	// Step in sequence
	bool sequence_previous_state = false;   // State of previous iteration
	int step_of_sequence = 0;				// 0 - sequence is not active / 1 - lighting rectangle / 2 - installing article
	int actual_length = 0;					// Program displays rectangle in 2nd step based on this value
	bool sequence_activated= false;


	std::vector <sf::RectangleShape> lighting_rectangles;
	std::vector <sf::RectangleShape> outline_rectangles;

	bool article_taken;						// checks if good article was taken from box
	bool article_installed;					// checks if article was installed and waits for confirmation


	//Constructor
	sfml_objects();

	// Initializations
	void init_button_size(float percentege_size);

	//Displaying objects
	void display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation);
	void display_texture(int pos_x, int pos_y, std::string file_path, int width, int height, float rotation);
	void display_text(int pos_x, int pos_y, std::string text, float size);
	void display_text(int pos_x, int pos_y, std::string text, float size, sf::Color color);

	//Accessors
	const bool getWindowIsOpen();

	// Detecting mouse collision with buttons
	bool detecting_green_button();
	bool detecting_red_button();

	//Functions
	void pollEvents(int &current_step);
	void update(int &current_step, std::vector <sData> &database);
	void render(int &current_step, int current_menu_window, std::vector<sf::RectangleShape>v_rectangles, std::vector <sData> &database);

private:

	int previous_step_of_sequence = 0;

	std::vector <std::string> list;											// Displays 2 previous, actual and following step in sequence
	int menu_window;

	//global timer variable
	bool timer_flag;
	bool sequence_start_flag;
	int displayed_time;
	sf::Clock clock;
	sf::Time time_elapsed;
	int calibration_time;
	bool if_clear = true;
	bool if_display=true;

	int green_rect_counter;
	int previos_loop_green_rect_counter;
	bool previous_wrong_state;
};

#endif