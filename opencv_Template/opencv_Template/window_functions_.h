#pragma once
#ifndef WINDOW_FUNCTIONS__H
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
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
	int step_of_sequence = 0;		// 0 - sequence is not active / 1 - lighting rectangle / 2 - installing article
	int actual_length = 0;			// Program displays rectangle in 2nd step based on this value
	bool sequence_activated= false;

	//bool back_to_menu;				// true if red button is activated. Program awaits confirmation of reset


	std::vector <sf::RectangleShape> lighting_rectangles;

	bool article_taken;						// checks if good article was taken from box
	bool article_installed;					// checks if article was installed and waits for confirmation


	//Constructor
	sfml_objects();

	// Initializations
	void init_button_size(float percentege_size);

	//Displaying objects
	void display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation);
	void display_text(int pos_x, int pos_y, std::string text, float size);

	//Accessors
	const bool getWindowIsOpen();

	// Detecting mouse collision with buttons
	bool detecting_green_button();
	bool detecting_red_button();

	//Functions
	void pollEvents(int &current_step, int &current_window);
	void update(int &current_step, int &current_window);
	void render(int current_step, int current_window);
};

#endif