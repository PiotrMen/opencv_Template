#pragma once
#ifndef WINDOW_FUNCTIONS__H
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>


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

	// blue button

	// length of sides in pixels
	int blue_button_length_x;
	int blue_button_length_y;

	//coordinates
	int blue_button_x;
	int blue_button_y;

	float button_size; //scaled button size (percentage)

	sf::RenderWindow *window;
	sf::Event event;
	//window size
	int window_width;
	int window_height;
	//Constructor
	sfml_objects();

	// Initializations
	void init_button_size(float percentege_size);

	//Displaying objects
	void display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation);
	void display_text(int pos_x, int pos_y, std::string text);

	//Accessors
	const bool getWindowIsOpen();

	// Detecting mouse collision with buttons
	bool detecting_green_button();
	bool detecting_red_button();

	//Functions
	void pollEvents();
	void update();
	void render();
	void left_mouse_button_pressed(int &current_step);
};

#endif