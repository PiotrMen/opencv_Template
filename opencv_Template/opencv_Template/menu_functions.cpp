#include "menu_functions.h"
#include <iostream>
#include "Universal_functions.h"
#include <string>


//Constructor
menu_sfml_objects::menu_sfml_objects()
{
	this->menu_window_height = 1080;
	this->menu_window_width = 1920;
	this->working_field_height = 675;
	this->working_field_width = 1200;
	this->menu_window = new sf::RenderWindow(sf::VideoMode(menu_window_width, menu_window_height), "Menu", sf::Style::Fullscreen);
	this->menu_window->requestFocus();
	this->menu_window->setMouseCursorGrabbed(true);

	//this->menu_window->setPosition(sf::Vector2i(0, -1080));
	this->enable_writing = false;

	for (int i = 0; i < 10; i++) {
		rectangles_saved = true;
		int k;
		sf::RectangleShape rect;
		k = 120;
		rect = making_rectangle(mm_to_pixels_converter(60 + (i * 120)), 400 + k, mm_to_pixels_converter(110), mm_to_pixels_converter(315), sf::Color::Red, 0);
		this->vector_rectangles.push_back(rect);
	}
}

// Initializations
void menu_sfml_objects::init_buttons_coords(){
	//length of sides in pixels

	//blue button
	this->blue_button_length_x = 124; // number of pixels (width and length of picture)
	this->blue_button_length_y = 124;

	//blue button
	this->Start_button_length_x = 124; // number of pixels (width and length of picture)
	this->Start_button_length_y = 124;

	//backward button
	this->backward_length_button_x = 512; // number of pixels (width and length of picture)
	this->backward_length_button_y = 512;

	//coordinates for blue button
	this->blue_button_x = this->menu_window_width - 200;  // 150 - number of pixels from bounds
	this->blue_button_y = this->menu_window_height - 150;

	//coordinates for blue button
	this->Start_button_x = this->menu_window_width - 200;  // 150 - number of pixels from bounds
	this->Start_button_y = this->menu_window_height - 150;

	//coordinates for backward button
	this->backward_button_x = 200;  // 150 - number of pixels from bounds
	this->backward_button_y = this->menu_window_height - 150;

	//length of sides for Select article button
	data_box.Upload_file_length_button_x = 707;
	data_box.Upload_file_length_button_y = 120;

	//coordinates for Upload file button
	this->load_csv_button_x = this->menu_window_width / 2;
	this->load_csv_button_y = 400;

	//coordinates for match boxes button
	this->installation_of_connectors_button_x = this->menu_window_width / 2;
	this->installation_of_connectors_button_y = load_csv_button_y + 200;

	//coordinates for connectors options button
	this->Calibration_button_x = this->menu_window_width / 2;
	this->Calibration_button_y = installation_of_connectors_button_y + 200;
}

void menu_sfml_objects::init_button_size(float percentege_size, float menu_button_percentege_size)
{
	this->button_size = percentege_size / 100;
	data_box.menu_button_size = menu_button_percentege_size / 100;
	this->backward_scale = 0.25;
}

//Displaying objects
void menu_sfml_objects::display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation)
{
	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/menu/" + file_path))
	{
		std::cerr << "Could not load texture" << std::endl;
		exit(1);
	}
	sf::Sprite texture;
	texture.setTexture(texture_);
	texture.setOrigin(sf::Vector2f(texture.getTexture()->getSize().x * 0.5, texture.getTexture()->getSize().y * 0.5));         //set origins of images to center
	texture.setPosition(pos_x, pos_y);
	texture.setScale(scale, scale);
	texture.setRotation(rotation);

	this->menu_window->draw(texture);
}
void menu_sfml_objects::display_texture(int pos_x, int pos_y, std::string file_path, float scale)
{
	//This function displays objects that are not guaranteed to exist
	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/menu/graphics_of_articles/" + file_path))
	{
	}
	else
	{
		sf::Sprite texture;
		texture.setTexture(texture_);
		texture.setOrigin(sf::Vector2f(texture.getTexture()->getSize().x * 0.5, texture.getTexture()->getSize().y * 0.5));         //set origins of images to center
		texture.setPosition(pos_x, pos_y);
		texture.setScale(scale, scale);

		this->menu_window->draw(texture);
	}
}

//Displaying text
void menu_sfml_objects::display_text(int pos_x, int pos_y, std::string text, float size)
{
	sf::Font font_;
	if (!font_.loadFromFile("resources/mermaid/Mermaid1001.ttf"))
	{
		std::cerr << "Could not load font" << std::endl;
		exit(1);
	}
	sf::Text text_;
	text_.setFillColor(sf::Color::Black);
	text_.setFont(font_);
	text_.setString(text);
	text_.setCharacterSize(size);
	text_.setOrigin((text_.getGlobalBounds().left + text_.getGlobalBounds().width) / 2, (text_.getGlobalBounds().height + text_.getGlobalBounds().top) / 2);     //set origins of text to center
	text_.setPosition(pos_x, pos_y);
	this->menu_window->draw(text_);
}

//Accessors
const bool menu_sfml_objects::getWindowIsOpen()
{
	return this->menu_window->isOpen();
}


// Detecting mouse collision with buttons
bool menu_sfml_objects::detecting_blue_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->blue_button_x - ((this->blue_button_length_x * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->blue_button_x + ((this->blue_button_length_x * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->blue_button_y - ((this->blue_button_length_y * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->blue_button_y + ((this->blue_button_length_y * this->button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_Upload_file_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->load_csv_button_x - ((data_box.Upload_file_length_button_x * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->load_csv_button_x + ((data_box.Upload_file_length_button_x * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->load_csv_button_y - ((data_box.Upload_file_length_button_y * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->load_csv_button_y + ((data_box.Upload_file_length_button_y * data_box.menu_button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_Match_boxes_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->installation_of_connectors_button_x - ((data_box.Upload_file_length_button_x * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->installation_of_connectors_button_x + ((data_box.Upload_file_length_button_x * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->installation_of_connectors_button_y - ((data_box.Upload_file_length_button_y * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->installation_of_connectors_button_y + ((data_box.Upload_file_length_button_y * data_box.menu_button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_calibration_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->Calibration_button_x - ((data_box.Upload_file_length_button_x * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->Calibration_button_x + ((data_box.Upload_file_length_button_x * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->Calibration_button_y - ((data_box.Upload_file_length_button_y * data_box.menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->Calibration_button_y + ((data_box.Upload_file_length_button_y * data_box.menu_button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_backward_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->backward_button_x - ((this->backward_length_button_x * this->backward_scale) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->backward_button_x + ((this->backward_length_button_x * this->backward_scale) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->backward_button_y - ((this->backward_length_button_y * this->backward_scale) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->backward_button_y + ((this->backward_length_button_y * this->backward_scale) / 2))))
	{
		return true;
	}
	return false;
}



//Egdes functions

bool menu_sfml_objects::detecting_rising_edge(bool signal){
	if (this->rising_edge_signal == false && signal) {
		this->rising_edge_detected_signal = true;
	}
	else {
		this->rising_edge_signal = false;
	}
	if (signal) {
		this->rising_edge_signal = true;
	}
	if (this->rising_edge_detected_signal) {
		this->rising_edge_detected_signal = false;
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_falling_edge(bool signal){
	if (this->falling_edge_signal == true && !signal) {
		this->falling_edge_detected_signal = true;
		this->falling_edge_signal = false;
	}
	if (signal) {
		this->falling_edge_signal = true;
	}
	if (this->falling_edge_detected_signal){
		this->falling_edge_detected_signal = false;
		this->falling_edge_signal = false;
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_rising_edge_left_mouse_button() {
	if (this->rising_edge == false && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		this->rising_edge_detected = true;
	}
	else{
		this->rising_edge = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->rising_edge = true;
	}
	if (this->rising_edge_detected) {
		this->rising_edge_detected = false;
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_falling_edge_left_mouse_button() {
	if (this->falling_edge == true && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->falling_edge_detected = true;
		this->falling_edge = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->falling_edge = true;
	}
	if (this->falling_edge_detected) {
		this->falling_edge_detected = false;
		this->falling_edge = false;
		return true;
	}
	return false;
}

//vector assigment
void menu_sfml_objects::assign_sequence()
{
	for (int i = 0; i < connectors_list.size(); i++)
	{
		for (int k = 0; k < sequence.size(); k++)
		{
			if (connectors_list[i].serial_number == sequence[k].serial_number)
				sequence[k].matched_rectangle = connectors_list[i].matched_rectangle;
		}
	}

}

//displaying underline
void menu_sfml_objects::display_underline()
{
	bool is_detected = unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window);

	if (is_detected != underline_detected_previous)
	{
		if_clear = true;
		if_display = true;
	}
	underline_detected_previous = is_detected;
}

//Functions
void menu_sfml_objects::pollEvents(int &current_step, int &current_window)
{
	//Event polling
	while (this->menu_window->pollEvent(this->event))
	{
		//do usuniecia

		//bool tmp = false;
		//
		switch (event.type)
		{
		case sf::Event::Closed:
			this->menu_window->close();
			break;

		case sf::Event::KeyPressed:
			//	if (event.key.code == sf::Keyboard::Escape)
			//	{
			//		data_box.global_exit = true;
			//	}

				// Handling CapsLock 
			if (event.key.code == -1)
			{
				if (caps_lock_pressed == true)
				{
					caps_lock_pressed = false;
				}
				else
				{
					caps_lock_pressed = true;
				}
			}
			//if ((event.key.code == sf::Keyboard::LAlt || event.key.code == sf::Keyboard::RAlt) || event.key.code == sf::Keyboard::Tab)
			//{
			//	if_display = true;
			//	if_clear = true;
			//}

			// Handling Shift
			shift_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
			if(shift_pressed == false)
				shift_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);


			// Handling Enter if input is in place
			if (event.key.code == sf::Keyboard::Enter && searching_text.size() > 0 && current_menu_window == 1)
			{
				this->current_menu_window = 0;

				//clearing vectors
				if (sequence_name != searching_text)
				{
					this->vector_displaying_articles.clear();
					this->connectors_list.clear();
					sequence.clear();
					this->start_sequention = false;
					this->which_box_is_writing = 0;
					this->which_box_chosen = 0;
					this->display_start_sequention = false;

					for (int i = 0; i < 10; i++) {
						vector_rectangles[i].setFillColor(sf::Color::Red);
					}

					// Execute loading
					load_csv_sequence(sequence, searching_text, connectors_list);
					sequence_name = searching_text;
					data_box.sequence_name = this->sequence_name;
					data_box.connectors_list_size = this->connectors_list.size();
				}
				searching_text.clear();
			}
			// Handling Enter if input is not in place
			if (event.key.code == sf::Keyboard::Enter)
			{
				enable_writing = false;
			}

			// Adding elements to string
			if (enable_writing == true && check_character(event.key.code, shift_pressed, caps_lock_pressed) != NULL && searching_text.size() < 28)
			{
				searching_text.push_back(check_character(event.key.code, shift_pressed, caps_lock_pressed));
			}

			// Deleting elements from string
			if (event.key.code == sf::Keyboard::BackSpace && enable_writing == true && searching_text.size() > 0)
			{
				searching_text.pop_back();
			}
			break;

		//case sf::Event::MouseButtonPressed:

		//	switch (event.key.code)
		//	{
		//	case sf::Mouse::Left:

		//		break;
		//	}
		//	break;
		}
	}
}

void menu_sfml_objects::update(int &current_step, int &current_window)
{
	if ((!this->was_window_idle && this->menu_window->hasFocus()) || (this->was_window_idle && !this->menu_window->hasFocus()))
	{
		if_display = true;
		if_clear = true;
	}
	this->was_window_idle = this->menu_window->hasFocus();

	this->pollEvents(current_step, current_window);
	rising_edge_saved = detecting_rising_edge_left_mouse_button();
	falling_edge_saved = detecting_falling_edge_left_mouse_button();
	if (sequence.size() == 0)
		sequence_name.clear();
	

	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(this->load_csv_button_x, this->load_csv_button_y, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window) && this->current_menu_window == 0) {
		//current_window = 1;
		this->current_menu_window = 1;
	}
	//Moving to match boxes section
	if (falling_edge_saved && detecting_Match_boxes_button() && this->current_menu_window == 0 && sequence.size() != 0) {
		this->current_menu_window = 2;
	}

	// section
	if (falling_edge_saved && detecting_calibration_button() && this->current_menu_window == 0) {
		this->current_menu_window = 3;
	}

	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(200, this->Start_button_y, this->Start_button_length_x, this->Start_button_length_y, data_box.menu_button_size, this->menu_window) && this->current_menu_window == 0)
		data_box.global_exit = true;

	//Backing to basic menu view
	if (detecting_backward_button() && falling_edge_saved && (current_menu_window == 1 || current_menu_window == 2 || current_menu_window == 3)) {
		searching_text.clear();
		this->current_menu_window = 0;
		this->enable_writing = false;
		this->if_clear = true;
		help_window_opened = true; // Zmienna aby nie przeskakiwa³o od razu do helpa
	}

	// Returning from help windows

	// Menu help window
	if (detecting_backward_button() && falling_edge_saved && current_menu_window == 100)
	{
		this->current_menu_window = 0;
		this->if_clear = true;
		help_window_opened = true;
	}

	// Loading .csv help window
	if (detecting_backward_button() && falling_edge_saved && current_menu_window == 101)
	{
		this->current_menu_window = 1;
		this->if_clear = true;
		help_window_opened = true;
	}

	// Matching boxes help window
	if (detecting_backward_button() && falling_edge_saved && current_menu_window == 102)
	{
		this->current_menu_window = 2;
		this->if_clear = true;
		help_window_opened = true;
	}

	// Tracing help window
	if (detecting_backward_button() && falling_edge_saved && current_menu_window == 103)
	{
		this->current_menu_window = 3;
		this->if_clear = true;
		help_window_opened = true;
	}

	//Calibration Camera section
	if (unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window) && falling_edge_saved && current_menu_window == 3) {
		this->current_menu_window = 301;
		data_box.camera_calibration = true;
		this->clock.restart();
	}

	if (this->current_menu_window == 301) {
		this->real_time = this->clock.getElapsedTime();
		this->displaying_time = this->time_compare.asSeconds() - this->real_time.asSeconds();

		if (this->real_time >= this->time_send_info)
			data_box.camera_calibration = false;

		if (this->real_time >= this->time_compare) {
			this->clock.restart();
			this->real_time = this->clock.restart();
			this->current_menu_window = 0;
		}
	}

	//Displaying help windows

//Menu help window
	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(this->blue_button_x, this->blue_button_y, this->blue_button_length_x, this->blue_button_length_y, data_box.menu_button_size, this->menu_window) && this->current_menu_window == 0 && help_window_opened == false)
	{
		this->current_menu_window = 100;
	}

	//Loading .csv help window
	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(this->blue_button_x, this->blue_button_y, this->blue_button_length_x, this->blue_button_length_y, data_box.menu_button_size, this->menu_window) && this->current_menu_window == 1 && help_window_opened == false)
	{
		this->current_menu_window = 101;
	}
	//Matching boxes help window
	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(this->blue_button_x, this->blue_button_y, this->blue_button_length_x, this->blue_button_length_y, data_box.menu_button_size, this->menu_window) && this->current_menu_window == 2 && help_window_opened == false)
	{
		this->current_menu_window = 102;
	}
	//Tracing help window
	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(this->blue_button_x, this->blue_button_y, this->blue_button_length_x, this->blue_button_length_y, data_box.menu_button_size, this->menu_window) && this->current_menu_window == 3 && help_window_opened == false)
	{
		this->current_menu_window = 103;
	}

	help_window_opened = false;

	//Confirming loading and moving to menu window
	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(990, 800, 707, 120, 1, this->menu_window) && this->current_menu_window == 1 && searching_text.size() > 0) {
		this->current_menu_window = 0;

		// Execute loading
		load_csv_sequence(sequence, searching_text, connectors_list);
		sequence_name = searching_text;
		data_box.connectors_list_size = this->connectors_list.size();
		searching_text.clear();
	}

	//Detecting cursor in searching square
	if (current_menu_window == 1 && rising_edge_saved && unieversal_detecting_collision_with_buttons(990, 400, 566, 99, 1, this->menu_window))
	{
		this->enable_writing = true;
	}
	//Deactivating cursor afrer clicking outside searching square
	if (current_menu_window != 1 || (current_menu_window == 1 && rising_edge_saved && !unieversal_detecting_collision_with_buttons(990, 400, 566, 99, 1, this->menu_window)))
	{
		this->enable_writing = false;
	}

	
	//serial numbers on rectangles
	if (current_menu_window == 2){
		bool if_wrong = true;
		display_underline();

		//if (vector_displaying_articles.size() - 1 == connectors_list.size())
		//	which_box_is_writing++;

		//detecting rectangles click
		for (int i = 0; i < which_box_is_writing; i++) {
			if (unieversal_detecting_collision_with_buttons(this->vector_rectangles[i].getPosition().x, this->vector_rectangles[i].getPosition().y, this->vector_rectangles[i].getGlobalBounds().width, this->vector_rectangles[i].getGlobalBounds().height, 1, this->menu_window) && falling_edge_saved && !change_number) {
				this->which_box_chosen = i;
				data_box.which_box_chosen = this->which_box_chosen;
				data_box.clicked_box = true;
				this->which_box_is_writing = this->which_box_chosen;
				change_number = true;
				vector_displaying_articles[which_box_is_writing].serial_number = 0;
				vector_displaying_articles[which_box_is_writing].name = "";
				vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Red);
				connectors_list[which_box_is_writing].repeated_number = false;
				connectors_list[which_box_is_writing].wrong_number = false;
				if_clear = true;
				if_display = true;
			}
		}
		if (unieversal_detecting_collision_with_buttons(this->vector_rectangles[which_box_is_writing].getPosition().x, this->vector_rectangles[which_box_is_writing].getPosition().y, this->vector_rectangles[which_box_is_writing].getGlobalBounds().width, this->vector_rectangles[which_box_is_writing].getGlobalBounds().height, 1, this->menu_window) && falling_edge_saved && !change_number)
		{
			change_number = true;
			data_box.which_box_chosen = this->which_box_is_writing;
			data_box.clicked_box = true;
			vector_displaying_articles[which_box_is_writing].serial_number = 0;
			vector_displaying_articles[which_box_is_writing].name = "";
			vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Red);
			connectors_list[which_box_is_writing].repeated_number = false;
			connectors_list[which_box_is_writing].wrong_number = false;
			if_clear = true;
			if_display = true;
		}

		this->start_sequention = false;
		this->enable_writing = true;

		if (previous_string.size() != searching_text.size()) {
			if_clear = true;
			if_display = true;
		}
		previous_string = searching_text;
		if (vector_displaying_articles.size() == 0) {
			vector_displaying_articles.push_back(this->empty);
		}

		//checking if numbers detected
		if (searching_text.size() > 0 && searching_text.size() <= 7) 
		{
			if (searching_text[searching_text.length() - 1] >= '0' && searching_text[searching_text.length() - 1] <= '9')
				vector_displaying_articles[which_box_is_writing].serial_number = stoi(searching_text);
			else
				searching_text.pop_back();
		}

		//checking corretness conectors

		//checking repeated conectors
		for (int i = 0; i < which_box_is_writing; i++) {
			vector_displaying_articles[which_box_is_writing].serial_number;
			if (vector_displaying_articles[i].serial_number == vector_displaying_articles[which_box_is_writing].serial_number) {
				vector_displaying_articles[which_box_is_writing].serial_number = 1;
				vector_displaying_articles[which_box_is_writing].matched_rectangle = which_box_is_writing;
				connectors_list[which_box_is_writing].repeated_number = true;
				connectors_list[which_box_is_writing].wrong_number = false;
				if_wrong = false;
				vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Red);
				this->display_start_sequention = false;
				change_number = false;
			}
		}

		for (int i = which_box_is_writing+1; i < vector_displaying_articles.size()-1; i++) {
			vector_displaying_articles[which_box_is_writing].serial_number;
			if (vector_displaying_articles[i].serial_number == vector_displaying_articles[which_box_is_writing].serial_number) {
				vector_displaying_articles[which_box_is_writing].serial_number = 1;
				vector_displaying_articles[which_box_is_writing].matched_rectangle = which_box_is_writing;
				connectors_list[which_box_is_writing].repeated_number = true;
				connectors_list[which_box_is_writing].wrong_number = false;
				if_wrong = false;
				vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Red);
				this->display_start_sequention = false;
				change_number = false;
			}
		}

		//checking good conectors
		for (int i = 0; i < connectors_list.size(); i++) {
			if ((vector_displaying_articles[which_box_is_writing].serial_number == connectors_list[i].serial_number)) {
				vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Green);
				vector_displaying_articles[which_box_is_writing].name = connectors_list[i].name;
				connectors_list[i].matched_rectangle = which_box_is_writing;
				connectors_list[which_box_is_writing].wrong_number = false;
				connectors_list[which_box_is_writing].repeated_number = false;
				if_wrong = false;
				change_number = false;
			}
			//checking wrong conectors
			if (searching_text.size() >= 7 && i == connectors_list.size()-1 && (vector_displaying_articles[which_box_is_writing].serial_number != connectors_list[i].serial_number) && if_wrong) {
				connectors_list[which_box_is_writing].wrong_number = true;
				connectors_list[which_box_is_writing].repeated_number = false;
				vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Red);
				if_wrong = true;
				this->display_start_sequention = false;
				change_number = false;
			}
		}

		//Moving iterator to the end of vector
		if (!change_number && which_box_chosen == which_box_is_writing && vector_displaying_articles.size()>1) {
			if(connectors_list.size() != vector_displaying_articles.size())
				vector_displaying_articles.erase(vector_displaying_articles.end() - 1);
			which_box_is_writing = vector_displaying_articles.size() - 1;
			if_clear = true;
			if_display = true;
		}

		//chcecking if 7 characters
		if (searching_text.size() >= 7 && vector_displaying_articles.size() <= 10 && !change_number) {
			vector_displaying_articles.push_back(this->empty);
			which_box_is_writing++;
			searching_text.clear();
			previous_string.clear();
		}

		//checking if every connectors are good
		if ((vector_displaying_articles.size()) >= connectors_list.size()) {
			for (int i = 0; i < connectors_list.size(); i++) {
				if (vector_rectangles[i].getFillColor() == (sf::Color::Green)) {
					i++;
				}
				else
				{
					this->display_start_sequention = false;
					break;
				}

				if (connectors_list.size() <= i) {
					this->display_start_sequention = true;
				}
				i--;
			}
		}

		//deleting last empty connetor
		if (connectors_list.size() <= which_box_is_writing || vector_displaying_articles.size() > 10) {
			vector_displaying_articles.erase(vector_displaying_articles.end() - 1);
			which_box_is_writing--;
			if_clear = true;
			if_display = true;
		}

		//start window clear if mouse is on start sequention button
		if ((rising_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window) && this->display_start_sequention) || (falling_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window) && this->display_start_sequention)) {
			if_clear = true;
			if_display = true;
		}

		//start sequention if button pushed or enter pressed
		if ((falling_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window) && this->display_start_sequention && !data_box.is_sequence_activated) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->display_start_sequention && !this->start_sequention))
		{
			this->start_sequention = true;
			this->display_start_sequention = false;
			assign_sequence();
			this->current_menu_window = 202;
			if_clear = true;
			if_display = true;
		}
	}
	else 
		data_box.calibration_box = false;

	// Sequence active
	if (this->current_menu_window == 202)
	{
		// Handling back to menu button
		if (falling_edge_saved && unieversal_detecting_collision_with_buttons(this->menu_window_width - 200, this->menu_window_height - 150, 124, 124, 1, this->menu_window) && this->timer_flag) {
			data_box.is_sequence_activated = false;
			data_box.last_step_of_sequence = true;
		}

		// Handling step back button
		if (falling_edge_saved && unieversal_detecting_collision_with_buttons(this->backward_button_x, this->backward_button_y, this->backward_length_button_x, this->backward_length_button_y, 1, this->menu_window) && this->timer_flag)
			data_box.step_back = true;

		//Handling text depends of global timer
		
		if (!this->timer_flag) {
			this->timer_flag = data_box.timer_done;
			this->real_time_calibration_freezed_screen = data_box.real_time_calibration_camera;
			this->displaying_time = this->invert_time_freezed_screen.asSeconds() - this->real_time_calibration_freezed_screen.asSeconds();
			if_clear = true;
			if_display = true;
		}

		//start window clear if mouse is on display live charts button
		if (this->live_chart_active && ((rising_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window)) || (falling_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window)))) {
			if_clear = true;
			if_display = true;
		}

		//start window clear underline on display live charts button
		if (this->live_chart_active && (detecting_falling_edge(unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window) && current_menu_window == 202) || (detecting_rising_edge(unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window) && current_menu_window == 202)))) {
			if_clear = true;
			if_display = true;
		}

		//going to 203
		if ((this->previous_current_menu_window==this->current_menu_window)&&(falling_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window))&&this->live_chart_active) {
			this->current_menu_window = 203;
			if_clear = true;
			if_display = true;
		}

	}

	if (this->current_menu_window == 202 && detecting_sequation_ending()) {
		//back to basic menu
		this->current_menu_window = 0;

		//clearing vectors
		this->vector_displaying_articles.clear();
		this->connectors_list.clear();
		sequence.clear();
		data_box.sequence_name.clear();
		//data_box.is_sequence_activated = false;
		this->start_sequention = false;
		this->which_box_is_writing = 0;
		this->which_box_chosen = 0;

		data_box.last_step_of_sequence = false;
		//data_box.v_actual_scanning_box_size = 0;

		//Clearing global vector
		//data_box.boxes.clear();
		if_clear = true;
		if_display = true;

		for (int i = 0; i < 10; i++) {
			vector_rectangles[i].setFillColor(sf::Color::Red);
		}
	}

	if (this->current_menu_window == 203 && detecting_sequation_ending()) {
		//back to basic menu
		this->current_menu_window = 0;

		//clearing vectors
		this->vector_displaying_articles.clear();
		this->connectors_list.clear();
		sequence.clear();
		data_box.sequence_name.clear();
		//data_box.is_sequence_activated = false;
		this->start_sequention = false;
		this->which_box_is_writing = 0;
		this->which_box_chosen = 0;

		data_box.last_step_of_sequence = false;
		//data_box.v_actual_scanning_box_size = 0;

		//Clearing global vector
		//data_box.boxes.clear();
		if_clear = true;
		if_display = true;

		for (int i = 0; i < 10; i++) {
			vector_rectangles[i].setFillColor(sf::Color::Red);
		}
	}

	this->previous_current_menu_window = this->current_menu_window;
}


//displaying graphics // current_menu_window - *
// 0 - basic menu
// 1 - Upload file .csv section
// 2 - match boxes section
// 3 - tracing section

//100 - Menu help window
//101 - Load .csv file help window
//102 - Match boxes help window
//103 - Tracing help window

//202 freezed screen with matched boxes
//203 live charts section


void menu_sfml_objects::render(int current_step, bool live_chart)
{
	this->live_chart_active = live_chart;

	if (if_clear)
		this->menu_window->clear(sf::Color(255, 255, 255, 255));
	//Basic menu window
	if (this->current_menu_window == 0) {
		//Displaying Upload file graphics
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_Upload_file_button())
			this->display_texture(this->load_csv_button_x, this->load_csv_button_y, "grey_pushed.png", data_box.menu_button_size, 0);
		else
			this->display_texture(this->load_csv_button_x, this->load_csv_button_y, "grey_button.png", data_box.menu_button_size, 0);

		//Displaying edit button graphics
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_Match_boxes_button())
			this->display_texture(this->installation_of_connectors_button_x, this->installation_of_connectors_button_y, "grey_pushed.png", data_box.menu_button_size, 0);
		else
			this->display_texture(this->installation_of_connectors_button_x, this->installation_of_connectors_button_y, "grey_button.png", data_box.menu_button_size, 0);

		//Displaying delete button graphics
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_calibration_button())
			this->display_texture(this->Calibration_button_x, this->Calibration_button_y, "grey_pushed.png", data_box.menu_button_size, 0);
		else
			this->display_texture(this->Calibration_button_x, this->Calibration_button_y, "grey_button.png", data_box.menu_button_size, 0);

		//Displaying blue button
		this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", this->button_size, 0);
		this->display_text(this->blue_button_x, this->blue_button_y + 75, "Pomoc", 30);

		//Displaying start button
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && unieversal_detecting_collision_with_buttons(200, this->Start_button_y, this->Start_button_length_x, this->Start_button_length_y, data_box.menu_button_size, this->menu_window))
			this->display_texture(200, this->Start_button_y, "red_circle_clicked.png", this->button_size, 0);
		else
			this->display_texture(200, this->Start_button_y, "red_circle.png", this->button_size, 0);

		this->display_text(200, this->Start_button_y + 75, "Exit", 30);

		//Texts
		Universal_display_text_polish_font(this->load_csv_button_x, this->load_csv_button_y - 10, L"Za³aduj plik .csv", 80,0,this->menu_window);
		//this->display_text(this->load_csv_button_x, this->load_csv_button_y - 10, "Zaladuj plik .csv", 80);
		this->display_text(this->installation_of_connectors_button_x, this->installation_of_connectors_button_y - 10, "Montaz zlaczek", 80);
		this->display_text(this->Calibration_button_x, this->Calibration_button_y - 10, "Kalibracja systemu", 80);
		this->display_text(this->menu_window_width / 2, 130, "Menu", 200);


		// Current sequence name
		this->display_text(225, 30, "Zaladowana sekwencja:", 34);
		if (sequence.size() == 0)
		{
			this->display_text(225, 80, "Brak", 34);
		}
		else
		{
			this->display_text(225, 80, sequence_name, 34);
		}

		//UnderLines
		if (detecting_Upload_file_button())
			this->display_texture(this->load_csv_button_x, this->load_csv_button_y + 85, "UnderLine.png", data_box.menu_button_size - 0.2, 0);

		if (detecting_Match_boxes_button())
			this->display_texture(this->installation_of_connectors_button_x, this->installation_of_connectors_button_y + 85, "UnderLine.png", data_box.menu_button_size - 0.2, 0);

		if (detecting_calibration_button())
			this->display_texture(this->Calibration_button_x, this->Calibration_button_y + 85, "UnderLine.png", data_box.menu_button_size - 0.2, 0);
	}

	if (this->current_menu_window == 100)
	{
		this->display_text(this->menu_window_width / 2, 130, "Pomoc", 200);

		// Displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
		this->display_text(this->backward_button_x, this->backward_button_y + 75, "Powrot", 30);

		// Displaying help
		this->display_text(this->menu_window_width/2, this->menu_window_height/2, load_txt_help("help_menu.txt"), 34);

	}

	//Upload file window displaying
	if (this->current_menu_window == 1) {
		//displaying name of section
		this->display_text(this->menu_window_width / 2, 130, "Zaladuj plik .csv", 200);

		//Displaying blue button
		this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", this->button_size, 0);
		this->display_text(this->blue_button_x, this->blue_button_y + 75, "Pomoc", 30);

		//displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
		this->display_text(this->backward_button_x, this->backward_button_y + 75, "Powrot", 30);

		//Displaying searching square
		if (this->enable_writing == true || this->searching_text.size() > 0)
		{
			this->display_texture(990, 400, "search_without_magnifying_glass.png", 1, 0);
		}
		else
		{
			this->display_texture(990, 400, "name.png", 1, 0);
		}
		this->display_text(990, 470, "Podaj nazwe wczytywanego pliku .csv", 26);
		this->display_text(990, 400, searching_text, 26);

		//Displaying acceptance button
		if (searching_text.size() > 0)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && unieversal_detecting_collision_with_buttons(990, 800, 707, 120, 1, this->menu_window))
			{
				this->display_texture(990, 800, "grey_pushed.png", data_box.menu_button_size, 0);
			}
			else
			{
				this->display_texture(990, 800, "grey_button.png", data_box.menu_button_size, 0);
			}
			this->display_text(990, 785, "Zatwierdz plik .csv", 80);

			//Button Underline
			if (unieversal_detecting_collision_with_buttons(990, 800, 707, 120, 1, this->menu_window))
			{
				this->display_texture(990, 800 + 85, "UnderLine.png", 0.9, 0);
			}
		}
	}
	if (this->current_menu_window == 101)
	{
		this->display_text(this->menu_window_width / 2, 130, "Pomoc", 200);

		// Displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
		this->display_text(this->backward_button_x, this->backward_button_y + 75, "Powrot", 30);

		// Displaying help
		this->display_text(this->menu_window_width / 2, this->menu_window_height / 2, load_txt_help("help_wczytanie_csv.txt"), 34);

	}

	//match boxes section displaying
	if (this->current_menu_window == 2 && if_clear) {

	//	std::cout << if_clear << "    " << if_display << std::endl;

		this->display_text(this->menu_window_width / 2, 130, "Zeskanuj pudelka", 200);

		//Displaying blue button
		this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", this->button_size, 0);
		this->display_text(this->blue_button_x, this->blue_button_y + 75, "Pomoc", 30);

		//displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
		this->display_text(this->backward_button_x, this->backward_button_y + 75, "Powrot", 30);

		//displaying rectangles
		for (int i = 0; i < 10; i++){
			this->menu_window->draw(this->vector_rectangles[i]);
			if(this->vector_rectangles[i].getFillColor() == sf::Color::Red)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y-30, std::to_string(i+1), 120);
			else
				display_texture(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y, std::to_string(vector_displaying_articles[i].serial_number) + ".png", 1);
		}

		//displaying texts on rectangle
		if(searching_text.size() != 0)
			this->display_text(vector_rectangles[which_box_is_writing].getPosition().x, vector_rectangles[which_box_is_writing].getPosition().y + 90, searching_text, 20);
		for (int i = 0; i < vector_displaying_articles.size(); i++) {
			if(!connectors_list[i].repeated_number && vector_displaying_articles[i].serial_number != 0 && i != which_box_is_writing)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y + 90, std::to_string(vector_displaying_articles[i].serial_number), 20);
			if (!connectors_list[i].repeated_number && std::to_string(vector_displaying_articles[i].serial_number).size() == 7 && i == which_box_is_writing)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y + 90, std::to_string(vector_displaying_articles[i].serial_number), 20);
			if(connectors_list[i].wrong_number)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 90, "Zly numer", 20);

			if(connectors_list[i].repeated_number)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 90, "Powtorzony numer", 20);

			if (!connectors_list[i].wrong_number && !connectors_list[i].repeated_number && vector_displaying_articles[i].name != "")
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 120, vector_displaying_articles[i].name, 16);
		}

		//displaying helpful text
		if (!this->display_start_sequention)
			this->display_text(960, 935, "Zeskanuj i poloz na stole zgodnie z instrukcja", 50);

		//displaying start sequention button
		if (this->display_start_sequention) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window) && this->display_start_sequention) {
				this->display_texture(960, 950, "grey_pushed.png", data_box.menu_button_size, 0);
				this->display_text(960, 935, "Start sekwencji", 100);
			}
			else {
				this->display_texture(960, 950, "grey_button.png", data_box.menu_button_size, 0);
				this->display_text(960, 935, "Start sekwencji", 100);
			}
			if(unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window))
				this->display_texture(960, 950 + 85, "UnderLine.png", data_box.menu_button_size - 0.2, 0);
		}
		this->if_clear = false;
	}

	if (this->current_menu_window == 102)
	{
		this->display_text(this->menu_window_width / 2, 130, "Pomoc", 200);

		// Displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
		this->display_text(this->backward_button_x, this->backward_button_y + 75, "Powrot", 30);

		// Displaying help
		this->display_text(this->menu_window_width / 2, this->menu_window_height / 2, load_txt_help("help_montaz_zlaczek.txt"), 34);

		this->if_clear = true;
	}

	//freezed screen when sequence started
	if (this->current_menu_window == 202 && if_clear) // && if_clear
	{
		//displaying rectangles
		for (int i = 0; i < 10; i++) {
			this->menu_window->draw(this->vector_rectangles[i]);
			if (this->vector_rectangles[i].getFillColor() == sf::Color::Red)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 30, std::to_string(i + 1), 120);
			else
				display_texture(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y, std::to_string(vector_displaying_articles[i].serial_number) + ".png", 1);
		}

		//displaying texts on rectangle
		this->display_text(vector_rectangles[which_box_is_writing].getPosition().x, vector_rectangles[which_box_is_writing].getPosition().y + 90, searching_text, 20);

		for (int i = 0; i < vector_displaying_articles.size(); i++) {
			if (!connectors_list[i].repeated_number && vector_displaying_articles[i].serial_number != 0)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y + 90, std::to_string(vector_displaying_articles[i].serial_number), 20);
			if (connectors_list[i].wrong_number)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 90, "Zly numer", 20);

			if (connectors_list[i].repeated_number)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 90, "Powtorzony numer", 20);

			if (!connectors_list[i].wrong_number && !connectors_list[i].repeated_number && vector_displaying_articles[i].name != "")
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 120, vector_displaying_articles[i].name, 16);
		}

		// Displaying step back in sequence
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
		this->display_text(this->backward_button_x, this->backward_button_y + 75, "Cofnij krok", 30);

		// Displaying back to menu in sequence
		this->display_texture(this->menu_window_width - 200, this->menu_window_height - 150, "red_circle.png", this->button_size, 0);
		this->display_text(this->menu_window_width - 200, this->menu_window_height - 75, "Powrot do menu", 30);

		if (!this->timer_flag) {
			this->display_text(920, 935, "Trwa kalibracja", 80);
			this->display_text(1270, 935, std::to_string(this->displaying_time) + " s:", 80);
		}
		
		if (live_chart) {
			//display go to Live Charts
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window)) {
				this->display_texture(960, 950, "grey_pushed.png", data_box.menu_button_size, 0);
				this->display_text(960, 935, "Wyswietl wykresy", 100);
			}
			else {
				this->display_texture(960, 950, "grey_button.png", data_box.menu_button_size, 0);
				this->display_text(960, 935, "Wyswietl wykresy", 100);
			}
			if (unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window))
				this->display_texture(960, 950 + 85, "UnderLine.png", data_box.menu_button_size - 0.2, 0);
		}
		this->if_clear = false;
	}

	//Calibration section section displaying
	if (this->current_menu_window == 3) {
		this->display_text(this->menu_window_width / 2, 130, "Kalibracja systemu", 200);

		//Displaying blue button
		this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", this->button_size, 0);
		this->display_text(this->blue_button_x, this->blue_button_y + 75, "Pomoc", 30);

		//displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
		this->display_text(this->backward_button_x, this->backward_button_y + 75, "Powrot", 30);

		this->display_text(this->menu_window_width / 2, 430, "Kalibrowanie punktow charakterystycznych:", 100);
		this->display_text(this->menu_window_width / 2, 530, "Sprawdz czy tasmy znajduja sie w podswietlonych miejscach", 60);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window)) {
			this->display_texture(960, 950, "grey_pushed.png", data_box.menu_button_size, 0);
			this->display_text(960, 930, "Zatwierdz", 100);
		}
		else {
			this->display_texture(960, 950, "grey_button.png", data_box.menu_button_size, 0);
			this->display_text(960, 930, "Zatwierdz", 100);
		}
		if (unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, this->menu_window))
			this->display_texture(960, 950 + 85, "UnderLine.png", data_box.menu_button_size - 0.2, 0);
	}

	if (this->current_menu_window == 301) {
		this->display_text(this->menu_window_width / 2, 130, "Kalibracja kamery", 200);
		this->display_text(this->menu_window_width / 2, 430, "Trwa kalibracja kamery, prosze poczekac", 100);
		this->display_text(this->menu_window_width / 2, 630, std::to_string(this->displaying_time) +" s:", 100);
		this->display_text(this->menu_window_width / 2, 830, "Sprawdz czy nic nie znajduje sie na stole", 60);
	}

	if (this->current_menu_window == 103)
	{
		this->display_text(this->menu_window_width / 2, 130, "Pomoc", 200);

		// Displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
		this->display_text(this->backward_button_x, this->backward_button_y + 75, "Powrot", 30);

		// Displaying help
		this->display_text(this->menu_window_width / 2, this->menu_window_height / 2, load_txt_help("help_kalibracja.txt"), 34);

	}

	if(if_display)
	this->menu_window->display();
	if (!if_clear)
		if_display = false;
	else
		if_display = true;
}
	
