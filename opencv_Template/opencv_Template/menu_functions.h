#pragma once
#ifndef MENU_WINDOW_FUNCTIONS_H
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "csv_read.h"
#include <SFML/System/Time.hpp>
#include <Windows.h>

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

	//Exit button
	// length of sides in pixels
	int Exit_button_length_x;
	int Exit_button_length_y;

	//coordinates
	int Exit_button_y;

	//coordinates 
	int load_csv_button_x;
	int load_csv_button_y;

	//coordinates 
	int installation_of_connectors_button_x;
	int installation_of_connectors_button_y;

	//coordinates 
	int Calibration_button_x;
	int Calibration_button_y;

	//start sequention
	bool start_sequention;

	float button_size; //scaled button size (percentage)

	sf::RenderWindow *menu_window;
	sf::Event event;

	// displaying and converting input text
	bool enable_writing; // enables writing after clicking on searching square
	std::string searching_text; // input text written by user
	bool shift_pressed;
	bool caps_lock_pressed;

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

	//This function displays objects that are not guaranteed to exist
	void display_texture(int pos_x, int pos_y, std::string file_path, float scale);
	void display_text(int pos_x, int pos_y, std::string text, float size);

	//Accessors
	const bool getWindowIsOpen();

	// Detecting mouse collision with buttons
	bool detecting_Upload_file_button();
	bool detecting_Match_boxes_button();
	bool detecting_calibration_button();
	bool detecting_backward_button();

	//Detecting rising/falling edges
	bool detecting_rising_edge_left_mouse_button();
	bool detecting_falling_edge_left_mouse_button();

	//Functions
	void pollEvents(int &current_step, int &current_window);
	void update(int &current_step, int &current_window);
	void render(int current_step, bool live_chart);

	// Functions
	char check_character(int key_number, bool shift_pressed, bool & caps_lock_pressed);

	int current_menu_window;
	std::vector<sf::RectangleShape> vector_rectangles;
	int which_box_is_writing = 0;

	//one time display if match boxes section
	bool if_clear = true;
	bool if_display = true;

private:

	bool detecting_rising_edge(bool signal);
	bool detecting_falling_edge(bool signal);
	//vector assigment
	void assign_sequence();

	//displaying underline
	void display_underline();

	bool rectangles_saved = false;
	// length of sides in pixels
	int backward_length_button_x;
	int backward_length_button_y;

	//which box chosen
	int which_box_chosen;

	//coordinates
	int backward_button_x;
	int backward_button_y;

	float backward_scale;

	//if display start sequention button
	bool display_start_sequention;

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
	
	bool help_window_opened;

	//underline detected in previous iteration
	bool underline_detected_previous = false;

	// vector of unique connectors from list
	std::vector <sData> vector_displaying_articles;

	//Name of csv sequence
	std::string sequence_name;

	std::vector <sData> connectors_list;

	bool change_number = false;

	sData empty;
	std::string previous_string;

	//Camera calibration variables
	sf::Time time_compare = sf::seconds(40);
	sf::Time time_send_info = sf::seconds(38);
	sf::Time real_time;

	int displaying_time;
	sf::Clock clock;

	// contains data about last state of window
	bool was_window_idle = false;

	int previous_current_menu_window;

	bool live_chart_active;
};

#endif