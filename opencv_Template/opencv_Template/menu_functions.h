#pragma once
#ifndef WINDOW_FUNCTIONS__H
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "articles.h"


class menu_sfml_objects
{
public:
	// blue button

	// length of sides in pixels
	int blue_button_length_x;
	int blue_button_length_y;

	//coordinates
	int blue_button_x;
	int blue_button_y;

	float button_size; //scaled button size (percentage)

	sf::RenderWindow *menu_window;
	sf::Event event;
	//window size
	int menu_window_width;
	int menu_window_height;
	//Constructor
	menu_sfml_objects();

	// Initializations
	void init_button_size(float percentege_size);

	//Displaying objects
	void display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation);
	void display_text(int pos_x, int pos_y, std::string text, float size);

	//Accessors
	const bool getWindowIsOpen();

	// Detecting mouse collision with buttons
	bool detecting_blue_button();

	//Functions
	void pollEvents(int &current_step, int &current_window);
	void update(int &current_step, int &current_window);
	void render(std::vector <sArticles> &articles, int current_step, int current_window);
};

#endif