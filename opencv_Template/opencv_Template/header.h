#pragma once
#ifndef HEADER_H
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>

class sfml_objects
{
public:
	sf::Sprite green_button;
	int green_button_x;
	int green_button_y;
	sf::RenderWindow *window;
	sf::Event event;

	//Constructor
	sfml_objects();

	//Displaying objects
	void display_next_button(int pos_x, int pos_y);

	//Accessors
	const bool getWindowIsOpen();

	//Functions
	void pollEvents();
	void update();
	void render();
};

#endif