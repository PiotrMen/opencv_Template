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

	//article select button

	//coordinates 
	int Select_article_button_x;
	int Select_article_button_y;

	//length of sides in pixels
	int Select_article_length_button_x;
	int Select_article_length_button_y;


	//add articles button

	//coordinates 
	int add_article_button_x;
	int add_article_button_y;

	//delete article button

	//coordinates 
	int delete_and_edit_article_button_x;
	int delete_and_edit_article_button_y;

	float button_size; //scaled button size (percentage)
	float menu_button_size;

	sf::RenderWindow *menu_window;
	sf::Event event;
	//window size
	int menu_window_width;
	int menu_window_height;
	//Constructor
	menu_sfml_objects();

	// Initializations
	void init_button_size(float percentege_size, float menu_button_percentege_size);
	void init_buttons_coords();

	//Displaying objects
	void display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation);
	void display_text(int pos_x, int pos_y, std::string text, float size);

	//Accessors
	const bool getWindowIsOpen();

	// Detecting mouse collision with buttons
	bool detecting_blue_button();
	bool detecting_Select_article_button();
	bool detecting_add_article_button();
	bool detecting_delete_and_edit_article_button();
	bool detecting_backward_button();
	bool unieversal_detecting_collision_with_buttons(int x, int y, int length_x, int length_y, float scale);

	//Detecting rising/falling edges
	bool detecting_rising_edge_left_mouse_button();
	bool detecting_falling_edge_left_mouse_button();

	//Functions
	void pollEvents(int &current_step, int &current_window);
	void update(int &current_step, int &current_window);
	void render(std::vector <sArticles> &articles, int current_step, int current_window);

	
	// addint_article.cpp

	// Functions
	char check_character(int key_number, bool shift_pressed, bool & caps_lock_pressed);

private:
	// backward button

	// length of sides in pixels
	int backward_length_button_x;
	int backward_length_button_y;

	//coordinates
	int backward_button_x;
	int backward_button_y;

	float backward_scale;

	bool rising_edge = false;
	bool rising_edge_detected = false;
	bool falling_edge = false;
	bool falling_edge_detected = false;
	int current_menu_window;
	bool falling_edge_saved;
};

#endif