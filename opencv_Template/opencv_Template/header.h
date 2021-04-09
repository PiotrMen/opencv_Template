#pragma once
#ifndef HEADER_H
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>


class sfml_objects
{
public:
	//coordinates for green button
	int green_button_x;
	int green_button_y;

	//coordinates for red button
	int red_button_x;
	int red_button_y;

	//coordinates for blue button
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
	void display_texture(int pos_x, int pos_y, std::string file_path, float scale_x, float scale_y);
	void display_text(int pos_x, int pos_y, std::string text);

	//Accessors
	const bool getWindowIsOpen();

	//Functions
	void pollEvents();
	void update();
	void render();
};

#endif