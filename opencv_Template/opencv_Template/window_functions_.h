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

	// Green button

	// Length of sides in pixels
	int green_button_length_x;
	int green_button_length_y;

	//Coordinates of green button
	int green_button_x;
	int green_button_y;

	float button_size; //scaled button size (percentage)

	// Window indicator (used for example in displaying textures)
	sf::RenderWindow *window;

	// Window size in pixels
	int window_width;
	int window_height;

	// Step in sequence
	bool sequence_previous_state = false;   // State of previous iteration
	int step_of_sequence = 0;				// 0 - sequence is not active / 1 - lighting rectangle / 2 - installing article
	bool sequence_activated = false;		// True if sequence is active. Sets step_of_sequence to 1 or 2. If false, sets step_of_sequence to 0.


	std::vector <sf::RectangleShape> lighting_rectangles;
	std::vector <sf::RectangleShape> outline_rectangles;

	bool article_taken;						// checks if good article was taken from box
	bool article_installed;					// checks if article was installed and waits for confirmation

	//Constructor
	sfml_objects();

	// Initializations
	void init_button_size(float percentege_size);

	//Displaying objects
	void display_texture(int pos_x, int pos_y, std::string file_path, int width, int height, float rotation);

	//Accessors
	const bool getWindowIsOpen();

	//Functions
	void update(int &current_step, std::vector <sData> &database);
	void render(int &current_step, int current_menu_window, std::vector<sf::RectangleShape>v_rectangles, std::vector <sData> &database, int which_box_is_writing);

private:

	int previous_step_of_sequence = 0;

	std::vector <std::string> list;			// List of actions displayed for user; Green - actions done; Yellow - current action; Red - awaiting actions				
				
	int menu_window;						// Stores data indicating which window is now open on second screen

	bool sequence_start_flag;				// Is used for setting sequence and activating it. After one loop, it is set to false.

	//	Variables used for displaying and measuring time during table calibration
	int displayed_time;				
	sf::Clock clock;
	sf::Time time_elapsed;
	int calibration_time;

	// Variables used for refreshing window
	bool if_clear = true;
	bool if_display=true;

	// Variables used in setting boxes before sequence has begun
	int green_rect_counter;
	int previos_loop_green_rect_counter;
	bool previous_wrong_state;
	int previous_box_writing;

	std::string sequence_name; // Used to check if sequence was changed. If was, clear data 
};
#endif