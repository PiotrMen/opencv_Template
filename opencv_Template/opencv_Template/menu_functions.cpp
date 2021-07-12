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
	this->menu_window->setPosition(sf::Vector2i(0, -1080));
	this->enable_writing = false;
}

// Initializations
void menu_sfml_objects::init_buttons_coords(){
	//length of sides in pixels

	//blue button
	this->blue_button_length_x = 414; // number of pixels (width and length of picture)
	this->blue_button_length_y = 414;

	//blue button
	this->Start_button_length_x = 414; // number of pixels (width and length of picture)
	this->Start_button_length_y = 414;

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
	this->Upload_file_length_button_x = 707;
	this->Upload_file_length_button_y = 120;

	//coordinates for Upload file button
	this->Upload_file_button_x = this->menu_window_width / 2;
	this->Upload_file_button_y = 400;

	//coordinates for match boxes button
	this->match_boxes_button_x = this->menu_window_width / 2;
	this->match_boxes_button_y = Upload_file_button_y + 200;

	//coordinates for connectors options button
	this->Connectors_options_button_x = this->menu_window_width / 2;
	this->Connectors_options_button_y = match_boxes_button_y + 200;
}

void menu_sfml_objects::init_button_size(float percentege_size, float menu_button_percentege_size)
{
	this->button_size = percentege_size / 100;
	this->menu_button_size = menu_button_percentege_size / 100;
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
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->Upload_file_button_x - ((this->Upload_file_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->Upload_file_button_x + ((this->Upload_file_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->Upload_file_button_y - ((this->Upload_file_length_button_y * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->Upload_file_button_y + ((this->Upload_file_length_button_y * this->menu_button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_Match_boxes_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->match_boxes_button_x - ((this->Upload_file_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->match_boxes_button_x + ((this->Upload_file_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->match_boxes_button_y - ((this->Upload_file_length_button_y * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->match_boxes_button_y + ((this->Upload_file_length_button_y * this->menu_button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_Connectors_options_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->Connectors_options_button_x - ((this->Upload_file_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->Connectors_options_button_x + ((this->Upload_file_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->Connectors_options_button_y - ((this->Upload_file_length_button_y * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->Connectors_options_button_y + ((this->Upload_file_length_button_y * this->menu_button_size) / 2))))
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
			if (event.key.code == sf::Keyboard::Escape)
			{
				this->menu_window->close();
			}

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

			// Handling Shift
			shift_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

			// Handling Enter if input is in place
			if (event.key.code == sf::Keyboard::Enter && searching_text.size() > 0)
			{
				this->current_menu_window = 0;
				// Execute loading
				load_csv_sequence(sequence, searching_text);
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

		case sf::Event::MouseButtonPressed:

			switch (event.key.code)
			{
			case sf::Mouse::Left:

			break;
			}
			break;
		}
	}
}

void menu_sfml_objects::update(int &current_step, int &current_window)
{
	this->pollEvents(current_step, current_window);
	rising_edge_saved = detecting_rising_edge_left_mouse_button();
	falling_edge_saved = detecting_falling_edge_left_mouse_button();

	//detecting rectangles click
	if (current_menu_window == 2) {
		for (int i = 0; i < 20; i++) {
			if (unieversal_detecting_collision_with_buttons(this->vector_rectangles[i].getPosition().x, this->vector_rectangles[i].getPosition().y, this->vector_rectangles[i].getGlobalBounds().width, this->vector_rectangles[i].getGlobalBounds().height, 1, this->menu_window) && falling_edge_saved) {
				this->which_box_chosen = i;
			}
		}
	}

	//Moving to Upload file .csv section
	/*if (falling_edge_saved && detecting_Upload_file_button() && this->current_menu_window == 0) {
		//current_window = 1;
		this->current_menu_window = 1;
	}*/
	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(this->Upload_file_button_x, this->Upload_file_button_y, this->Upload_file_length_button_x, this->Upload_file_length_button_y, this->menu_button_size, this->menu_window) && this->current_menu_window == 0) {
		//current_window = 1;
		this->current_menu_window = 1;
	}
	//Moving to match boxes section
	if (falling_edge_saved && detecting_Match_boxes_button() && this->current_menu_window == 0) {
		this->current_menu_window = 2;
	}

	//Moving to connectors options section
	if (falling_edge_saved && detecting_Connectors_options_button() && this->current_menu_window == 0) {
		this->current_menu_window = 3;
	}

	//Backing to basic menu view
	if (detecting_backward_button() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && (current_menu_window == 1 || current_menu_window == 2 || current_menu_window == 3)) {
		searching_text.clear();
		this->current_menu_window = 0;
		this->enable_writing = false;
		this->if_clear = true;
	}
	
	//Confirming loading and moving to menu window
	if (falling_edge_saved && unieversal_detecting_collision_with_buttons(990, 800, 707, 120, 1, this->menu_window) && this->current_menu_window == 1 && searching_text.size() > 0) {
		this->current_menu_window = 0;
		// Execute loading
		load_csv_sequence(sequence, searching_text);
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
	
	//saving rectangles to the vector
	if (current_menu_window == 2 && !rectangles_saved) {
		for (int i = 0; i < 20; i++) {
			rectangles_saved = true;
			int k;
			sf::RectangleShape rect;
			if (i >= 10) {
				k = mm_to_pixels_converter(175);
				rect = making_rectangle(mm_to_pixels_converter(60 + (i * 120) - 1200), 400 + k, mm_to_pixels_converter(110), mm_to_pixels_converter(165), sf::Color::Red, 0);
				this->vector_rectangles.push_back(rect);
			}
			else {
				k = 0;
				rect = making_rectangle(mm_to_pixels_converter(60 + (i * 120)), 400 + k, mm_to_pixels_converter(110), mm_to_pixels_converter(165), sf::Color::Red, 0);
				this->vector_rectangles.push_back(rect);
			}
		}
	}
	
	//serial numbers on rectangles
	if (current_menu_window == 2){

		this->enable_writing = true;
		bool if_wrong = true;

		if (previous_string.size() < searching_text.size()) {
			if_clear = true;
			if_display = true;
		}
		previous_string = searching_text;
		if (vector_displaying_articles.size() == 0) {
			vector_displaying_articles.push_back(this->empty);
		}

		//checking if numbers detected
		if (searching_text.size() > 0 && searching_text.size() <= 7) {
			if (searching_text[searching_text.length()-1] >= '0' && searching_text[searching_text.length()-1] <= '9')
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
				sequence[which_box_is_writing].repeated_number = true;
				sequence[which_box_is_writing].wrong_number = false;
				if_wrong = false;
				vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Red);
				this->display_start_sequention = false;
			}
		}

		//checking good conectors
		for (int i = 0; i < sequence.size(); i++) {
			if ((vector_displaying_articles[which_box_is_writing].serial_number == sequence[i].serial_number)) {
				vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Green);
				sequence[i].matched_rectangle = which_box_is_writing;
				sequence[which_box_is_writing].wrong_number = false;
				sequence[which_box_is_writing].repeated_number = false;
				if_wrong = false;
			}
			//checking wrong conectors
			if (searching_text.size() >= 7 && i == sequence.size()-1 && (vector_displaying_articles[which_box_is_writing].serial_number != sequence[i].serial_number) && if_wrong) {
				sequence[which_box_is_writing].wrong_number = true;
				sequence[which_box_is_writing].repeated_number = false;
				vector_rectangles[which_box_is_writing].setFillColor(sf::Color::Red);
				if_wrong = true;
				this->display_start_sequention = false;
			}
		}

		//chcecking if 7 characters
		if (searching_text.size() >= 7 && vector_displaying_articles.size() < 20) {
			vector_displaying_articles.push_back(this->empty);
			which_box_is_writing++;
			searching_text.clear();
			previous_string.clear();
		}

		//checking if every connectors are good
		if ((vector_displaying_articles.size()) >= sequence.size()) {
			for (int i = 0; i < sequence.size(); i++) {
				if (vector_rectangles[i].getFillColor() == (sf::Color::Green)) {
					i++;
				}
				else
					break;
				if (sequence.size() <= i) {
					this->display_start_sequention = true;
				}
				i--;
			}
		}

		if (sequence.size() <= which_box_is_writing) {
			vector_displaying_articles.erase(vector_displaying_articles.end() - 1);
			which_box_is_writing--;
			if_clear = true;
			if_display = true;
		}
		if (unieversal_detecting_collision_with_buttons(960, 950, this->Upload_file_length_button_x, this->Upload_file_length_button_y, this->menu_button_size, this->menu_window) && this->display_start_sequention) {
			if_clear = true;
			if_display = true;
		}
		if (falling_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, this->Upload_file_length_button_x, this->Upload_file_length_button_y, this->menu_button_size, this->menu_window) && this->display_start_sequention) 
			this->start_sequention = true;
		
	}
}


//displaying graphics // current_menu_window - *
// 0 - basic menu
// 1 - Upload file .csv section
// 2 - match boxes section
// 3 - connectors options section

void menu_sfml_objects::render(int current_step, int current_window)
{
	if(if_clear)
		this->menu_window->clear(sf::Color(255, 255, 255, 255));
	//Basic menu window
	if (this->current_menu_window == 0) {
		//Displaying Upload file graphics
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_Upload_file_button()) 
			this->display_texture(this->Upload_file_button_x, this->Upload_file_button_y, "grey_pushed.png", this->menu_button_size, 0);
		else
			this->display_texture(this->Upload_file_button_x, this->Upload_file_button_y, "grey_button.png", this->menu_button_size, 0);

		//Displaying edit button graphics
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_Match_boxes_button())
			this->display_texture(this->match_boxes_button_x, this->match_boxes_button_y, "grey_pushed.png", this->menu_button_size, 0);
		else
			this->display_texture(this->match_boxes_button_x, this->match_boxes_button_y, "grey_button.png", this->menu_button_size, 0);

		//Displaying delete button graphics
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_Connectors_options_button())
			this->display_texture(this->Connectors_options_button_x, this->Connectors_options_button_y, "grey_pushed.png", this->menu_button_size, 0);
		else
			this->display_texture(this->Connectors_options_button_x, this->Connectors_options_button_y, "grey_button.png", this->menu_button_size, 0);

		//Displaying blue button
		this->display_texture(200, this->blue_button_y, "blue_circle.png", this->button_size, 0);
		this->display_text(200, this->blue_button_y + 75, "Pomoc", 30);

		//Displaying start button
		this->display_texture(this->Start_button_x, this->Start_button_y, "green_circle.png", this->button_size, 0);
		this->display_text(this->Start_button_x, this->Start_button_y + 75, "Start", 30);

		//Texts
		this->display_text(this->Upload_file_button_x, this->Upload_file_button_y - 10, "Zaladuj plik .csv", 80);
		this->display_text(this->match_boxes_button_x, this->match_boxes_button_y - 10, "Montaz zlaczek", 80);
		this->display_text(this->Connectors_options_button_x, this->Connectors_options_button_y - 10, "Ustawienia zlaczek", 80);
		this->display_text(this->menu_window_width / 2, 130, "Menu", 200);

		//UnderLines
		if (detecting_Upload_file_button())
			this->display_texture(this->Upload_file_button_x, this->Upload_file_button_y + 85, "UnderLine.png", this->menu_button_size - 0.2, 0);

		if (detecting_Match_boxes_button())
			this->display_texture(this->match_boxes_button_x, this->match_boxes_button_y + 85, "UnderLine.png", this->menu_button_size - 0.2, 0);

		if (detecting_Connectors_options_button())
			this->display_texture(this->Connectors_options_button_x, this->Connectors_options_button_y + 85, "UnderLine.png", this->menu_button_size - 0.2, 0);
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
				this->display_texture(990, 800, "grey_pushed.png", this->menu_button_size, 0);
			}
			else
			{
				this->display_texture(990, 800, "grey_button.png", this->menu_button_size, 0);
			}
			this->display_text(990, 785, "Zatwierdz plik .csv", 80);

			//Button Underline
			if (unieversal_detecting_collision_with_buttons(990, 800, 707, 120, 1, this->menu_window))
			{
				this->display_texture(990, 800 + 85, "UnderLine.png", 0.9, 0);
			}
		}
	}

	//match boxes section displaying
	if (this->current_menu_window == 2 && if_clear) {
		this->display_text(this->menu_window_width / 2, 130, "Zeskanuj pudelka", 200);

		//Displaying blue button
		this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", this->button_size, 0);
		this->display_text(this->blue_button_x, this->blue_button_y + 75, "Pomoc", 30);

		//displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);

		//displaying rectangles
		for (int i = 0; i < 20; i++){
			this->menu_window->draw(this->vector_rectangles[i]);
			this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y-30, std::to_string(i+1), 120);
		}

		//displaying texts on rectangle
		this->display_text(vector_rectangles[which_box_is_writing].getPosition().x, vector_rectangles[which_box_is_writing].getPosition().y + 90, searching_text, 20);

		for (int i = 0; i < which_box_is_writing+1; i++) {
			if(!sequence[i].repeated_number && vector_displaying_articles[i].serial_number != 0)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y + 90, std::to_string(vector_displaying_articles[i].serial_number), 20);
			if(sequence[i].wrong_number)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 90, "Zly numer", 20);

			if(sequence[i].repeated_number)
				this->display_text(vector_rectangles[i].getPosition().x, vector_rectangles[i].getPosition().y - 90, "Powtorzony numer", 20);
		}

		//displaying start sequention button
		if (this->display_start_sequention) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && unieversal_detecting_collision_with_buttons(960, 950, this->Upload_file_length_button_x, this->Upload_file_length_button_y, this->menu_button_size, this->menu_window) && this->display_start_sequention) {
				this->display_texture(960, 950, "grey_pushed.png", this->menu_button_size, 0);
				this->display_text(960, 935, "Start sekwencji", 100);
			}
			else {
				this->display_texture(960, 950, "grey_button.png", this->menu_button_size, 0);
				this->display_text(960, 935, "Start sekwencji", 100);
			}
			if(unieversal_detecting_collision_with_buttons(960, 950, this->Upload_file_length_button_x, this->Upload_file_length_button_y, this->menu_button_size, this->menu_window))
				this->display_texture(960, 950 + 85, "UnderLine.png", this->menu_button_size - 0.2, 0);
		}
		this->if_clear = false;
	}

	//connectors options section displaying
	if (this->current_menu_window == 3) {
		this->display_text(this->menu_window_width / 2, 130, "Ustawienia zlaczek", 200);

		//Displaying blue button
		this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", this->button_size, 0);
		this->display_text(this->blue_button_x, this->blue_button_y + 75, "Pomoc", 30);

		//displaying backward in section
		this->display_texture(this->backward_button_x, this->backward_button_y, "backward.png", this->backward_scale, 0);
	}

	if(if_display)
	this->menu_window->display();
	if (!if_clear)
		if_display = false;
	else
		if_display = true;
}
	
