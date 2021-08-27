#include "window_functions_.h"


//Constructor
sfml_objects::sfml_objects()
{
	this->window_height = 1080;
	this->window_width = 1920;
	this->window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), "Window", sf::Style::Fullscreen);
	this->window->setPosition(sf::Vector2i(0, -1080));
	for (int i = 0; i < 10; i++)
	{
		sf::RectangleShape rect_empty;
		sf::RectangleShape rect_filled;
		rect_empty = making_rectangle(mm_to_pixels_converter(60 + (i * 120)), 262, mm_to_pixels_converter(110), mm_to_pixels_converter(315), sf::Color::Green, 0);
		/*if(i == 0 || i == 9 || i == 4 || i == 5)
			rect_filled = making_rectangle(mm_to_pixels_converter(60 + (i * 120)), 290, mm_to_pixels_converter(120), mm_to_pixels_converter(315), sf::Color::Green, 0);
		else if(i < 4)
			rect_filled = making_rectangle(mm_to_pixels_converter(60 + (i * 120)) - mm_to_pixels_converter(17 - i * 5), 290, mm_to_pixels_converter(120), mm_to_pixels_converter(315), sf::Color::Green, 0);
		else
			rect_filled = making_rectangle(mm_to_pixels_converter(60 + (i * 120)) + mm_to_pixels_converter(i * 5 - 28), 290, mm_to_pixels_converter(120), mm_to_pixels_converter(315), sf::Color::Green, 0);*/
		this->outline_rectangles.push_back(rect_empty);
		this->lighting_rectangles.push_back(rect_empty);

		//this->lighting_rectangles.push_back(rect_filled);
	}

	// sfml data to opencv
	data_box.boxes = lighting_rectangles;
}


// Initializations
void sfml_objects::init_button_size(float percentege_size)
{
	//length of sides in pixels

	//green button
	this->green_button_length_x = 124; // number of pixels (width and length of picture)
	this->green_button_length_y = 124;

	//coordinates for green button
	this->green_button_x = this->window_width - 75 - ((this->green_button_length_x / 2) * percentege_size / 100);  // 150 - number of pixels from 
	this->green_button_y = this->window_height - 50 - ((this->green_button_length_y / 2) * percentege_size / 100);

	//red button
	this->red_button_length_x = 124;
	this->red_button_length_y = 124;

	//coordinates for red button
	this->red_button_x = 75 + ((this->red_button_length_x / 2) * percentege_size / 100);
	this->red_button_y = this->window_height - 75 - ((this->red_button_length_y / 2) * percentege_size / 100);


	this->button_size = percentege_size / 100;
}

//Displaying objects
void sfml_objects::display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation)
{
	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/" + file_path))
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

	this->window->draw(texture);
}

void sfml_objects::display_texture(int pos_x, int pos_y, std::string file_path, int width, int height, float rotation)
{
	//Function used for displaying textures of connectors on projector

	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/" + file_path))
	{
		sf::RectangleShape lacking_connector = making_rectangle(pos_x, pos_y, width, height, sf::Color::Green, false);
		this->window->draw(lacking_connector);
	}
	else
	{
		sf::Sprite texture;
		texture.setTexture(texture_);
		texture.setOrigin(sf::Vector2f(texture.getTexture()->getSize().x * 0.5, texture.getTexture()->getSize().y * 0.5));         //set origins of images to center
		texture.setPosition(pos_x, pos_y);
		texture.setScale(width / texture.getGlobalBounds().width, height / texture.getGlobalBounds().height);
		texture.setRotation(rotation);

		this->window->draw(texture);
	}
}

//Displaying text
void sfml_objects::display_text(int pos_x, int pos_y, std::string text, float size)
{
	sf::Font font_;
	if (!font_.loadFromFile("resources/mermaid/Mermaid1001.ttf"))
	{
		std::cerr << "Could not load font" << std::endl;
		exit(1);
	}
	sf::Text text_;
	text_.setFillColor(sf::Color::White);
	text_.setFont(font_);
	text_.setString(text);
	text_.setCharacterSize(size);
	text_.setOrigin((text_.getGlobalBounds().left + text_.getGlobalBounds().width) / 2, 0);     //set origins of text to center
	text_.setPosition(pos_x, pos_y);
	this->window->draw(text_);
}

void sfml_objects::display_text(int pos_x, int pos_y, std::string text, float size, sf::Color color)
{
	sf::Font font_;
	if (!font_.loadFromFile("resources/mermaid/Mermaid1001.ttf"))
	{
		std::cerr << "Could not load font" << std::endl;
		exit(1);
	}
	sf::Text text_;
	text_.setFillColor(color);
	text_.setFont(font_);
	text_.setString(text);
	text_.setCharacterSize(size);
	text_.setOrigin(0, 0);     //set origins to 0
	text_.setPosition(pos_x, pos_y);
	this->window->draw(text_);
}

//Accessors
const bool sfml_objects::getWindowIsOpen()
{
	return this->window->isOpen();
}

// Detecting mouse collision with buttons
bool sfml_objects::detecting_green_button()
{
	if (((sf::Mouse::getPosition(*this->window).x >= this->green_button_x - ((this->green_button_length_x * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->window).x <= this->green_button_x + ((this->green_button_length_x * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->window).y >= this->green_button_y - ((this->green_button_length_y * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->window).y <= this->green_button_y + ((this->green_button_length_y * this->button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool sfml_objects::detecting_red_button()
{
	if (((sf::Mouse::getPosition(*this->window).x >= this->red_button_x - ((this->red_button_length_x * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->window).x <= this->red_button_x + ((this->red_button_length_x * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->window).y >= this->red_button_y - ((this->red_button_length_y * this->button_size) / 2)) && (sf::Mouse::getPosition(*this->window).y <= this->red_button_y + ((this->red_button_length_y * this->button_size) / 2))))
	{
		return true;
	}
	return false;
}


//Functions
void sfml_objects::pollEvents(int &current_step)
{
	//Event polling
	while (this->window->pollEvent(this->event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::MouseButtonPressed:
		{
			switch (event.key.code)
			{
			case sf::Mouse::Right:
			{

				// do testow, przechodzenie do kolejnego kroku na prawy przycisk myszy w window functions
				if (this->step_of_sequence == 1)
				{
					//data_box.detecting_box = true;
					//
					//Sleep(500);
				}


				if (this->step_of_sequence == 2)
				{
					//data_box.green_button = true;
					//Sleep(500);
				}

				//

				break;
			}

			case sf::Mouse::Left:
			{
				break;
			}
			}
			break;
		}
		}
	}
}

void sfml_objects::update(int &current_step, std::vector <sData> &database)
{
	this->pollEvents(current_step);

	if (!this->timer_flag)
		this->timer_flag = data_box.timer_done;

	if (!this->sequence_previous_state && this->sequence_activated)
	{
		this->sequence_start_flag = true;
		if_clear = true;
		if_display = true;
	}

	if (this->sequence_start_flag && this->timer_flag)
	{
		// sfml data to opencv
		data_box.is_sequence_activated = this->sequence_activated;

		// Initializing sequence list

		list.push_back("1.1 Pobranie " + sequence[0].name);				//Actual step
		list.push_back("1.2 Instalacja " + sequence[0].name);			//Following step

		// Checking if sequence elements match with database
		for (int i = 0; i < sequence.size(); i++)
		{
			for (int k = 0; k < database.size(); k++)
			{
				if (sequence[i].serial_number == database[k].serial_number)
				{
					sequence[i].height = database[k].height;
					sequence[i].width = database[k].width;
				}
			}
		}


		this->step_of_sequence = 1;
		this->sequence_start_flag = false;
	}
	
	// Checking if article was taken
	if (data_box.detecting_box && this->step_of_sequence == 1)
	{
		this->article_taken = true;
	}
	// Waiting for confirmation in step 2
	if (data_box.green_button && this->step_of_sequence == 2)
	{
		this->article_installed = true;
	}

	// Go back to previous step in sequence

	if (data_box.step_back == true)
	{
		if (this->step_of_sequence == 2 && sequence.size() > 1)
		{
			this->step_of_sequence = 1;

			if (current_step < sequence.size() - 1)
				list.pop_back();
			if(current_step > 0)
				list.insert(list.begin(), 1, std::to_string(current_step) + "." + std::to_string(1) + " Pobranie " + sequence[current_step - 1].name);
		}
		else if (this->step_of_sequence == 2 && sequence.size() == 1)
		{
			list.insert(list.begin(), 1, std::to_string(1) + "." + std::to_string(1) + " Pobranie " + sequence[0].name);
			this->step_of_sequence = 1;
		}
		else if (this->step_of_sequence == 1 && current_step > 0)
		{
			this->step_of_sequence = 2;
			current_step--;

			if (current_step < sequence.size())
				list.pop_back();
			if(current_step > 0)
				list.insert(list.begin(), 1, std::to_string(current_step) + "." + std::to_string(2) + " Instalacja " + sequence[current_step - 1].name);
		}
		data_box.step_back = false;
	}
	if (this->menu_window == 3)
	{
		this->clock.restart();
		this->calibration_time = 39;
	}

	if (this->menu_window == 301)
	{
		this->time_elapsed = clock.getElapsedTime();
		if ((int)this->time_elapsed.asSeconds() != 39 - this->displayed_time)
		{
			if (this->displayed_time >= 0)
				this->displayed_time = this->calibration_time - (int)this->time_elapsed.asSeconds();
			if_clear = true;
			if_display = true;
		}
	}


	if (data_box.is_sequence_activated == false)
		step_of_sequence = 0;
	this->sequence_previous_state = this->sequence_activated;

	if ((this->step_of_sequence != this->previous_step_of_sequence)||(data_box.wrong_box != this->previous_wrong_state)) {
		if_clear = true;
		if_display = true;
	}
	this->previous_wrong_state = data_box.wrong_box;
	this->previous_step_of_sequence = this->step_of_sequence;

	if (data_box.checking_boxes_state) {
		if_clear = true;
		if_display = true;
		data_box.checking_boxes_state = false;
	}


}


void sfml_objects::render(int &current_step, int current_menu_window, std::vector<sf::RectangleShape>v_rectangles, std::vector <sData> &database, int which_box_is_writing)
{

	if (current_menu_window == 2) {

		//freezing window function
		for (int i = 0; i < v_rectangles.size(); i++) {
			if (v_rectangles[i].getFillColor() == (sf::Color::Green)) {
				this->green_rect_counter++;
			}
		}

		//searching adding box
		if (this->green_rect_counter > this->previos_loop_green_rect_counter) {
			if_clear = true;
			if_display = true;
		}

		//searching erasing box
		if (data_box.clicked_box ) {
			if_clear = true;
			if_display = true;
		}

		for (int i = 0; i < data_box.index_and_checked_info_accepted_boxes.size(); i++)
		{
			if (v_rectangles[i].getFillColor() == sf::Color::Red && data_box.index_and_checked_info_accepted_boxes[i].second != 2)
			{
				data_box.index_and_checked_info_accepted_boxes[i] = std::make_pair(i, 2);
				if_clear = true;
				if_display = true;
			}
			else if (v_rectangles[i].getFillColor() == sf::Color::Green && data_box.index_and_checked_info_accepted_boxes[i].second == 2)
			{
				data_box.index_and_checked_info_accepted_boxes[i] = std::make_pair(i, 0);
				if_clear = true;
				if_display = true;
			}
		}
	}

	if (this->menu_window != current_menu_window) {
		if_clear = true;
		if_display = true;
	}

	if (this->previous_box_writing < which_box_is_writing) {
		if_clear = true;
		if_display = true;
	}

	if (this->menu_window == 301) 
	{
		this->window->clear(sf::Color(255, 255, 255, 255));
	}
	else if (if_clear || this->menu_window == 0)
	{
		if_clear = true;
		if_display = true;
		this->window->clear(sf::Color(0, 0, 0, 255));
	}


	this->menu_window = current_menu_window;
	if (current_menu_window == 2 && if_clear) 
	{

		if ((this->previous_box_writing < which_box_is_writing)|| ((v_rectangles[data_box.connectors_list_size-1].getFillColor() == (sf::Color::Green)) && (data_box.connectors_list_size == this->previous_box_writing+1))) {
			if (data_box.connectors_list_size > data_box.index_and_checked_info_accepted_boxes.size()) {
				if(v_rectangles[this->previous_box_writing].getFillColor() == (sf::Color::Green))
					data_box.index_and_checked_info_accepted_boxes.push_back(std::make_pair(this->previous_box_writing, 0));
				else
					data_box.index_and_checked_info_accepted_boxes.push_back(std::make_pair(this->previous_box_writing, 2));
				this->previous_box_writing++;
			}
		}

		for (int i = 0; i < v_rectangles.size(); i++) {
			if (v_rectangles[i].getFillColor() == (sf::Color::Green)) {
				//start calibration boxes
				data_box.calibration_box = true;
			}
		}

		//erasing box after clicking
		if (data_box.clicked_box) 
			data_box.clicked_box = false;

		for (int i = 0; i < data_box.index_and_checked_info_accepted_boxes.size(); i++) 
		{
			sf::RectangleShape rectangle_;

			rectangle_.setSize(sf::Vector2f(mm_to_pixels_converter(95), mm_to_pixels_converter(25)));
			rectangle_.setOrigin(sf::Vector2f(rectangle_.getSize().x / 2, rectangle_.getSize().y / 2));
			rectangle_.setPosition(this->outline_rectangles[data_box.index_and_checked_info_accepted_boxes[i].first].getPosition().x, this->outline_rectangles[data_box.index_and_checked_info_accepted_boxes[i].first].getPosition().y + this->outline_rectangles[data_box.index_and_checked_info_accepted_boxes[i].first].getSize().y / 2);
			if (data_box.index_and_checked_info_accepted_boxes[i].second == 0)
				rectangle_.setFillColor(sf::Color::Red);
			else if(data_box.index_and_checked_info_accepted_boxes[i].second == 1)
				rectangle_.setFillColor(sf::Color::Green);
			else if (data_box.index_and_checked_info_accepted_boxes[i].second == 2)
				rectangle_.setFillColor(sf::Color::Black);

			this->window->draw(rectangle_);
		}


		//displaying helpful graphics
		this->display_texture(this->window_width / 2 -300 , 780, "dobry_wzor.png", 0.35, 0);
		this->display_texture(this->window_width / 2 + 300, 780, "Zly_wzor.png", 0.35, 0);
		this->display_texture(this->window_width / 2 , 780, "Zly_wzor2.png", 0.35, 0);

		//displaying good and wrong example
		this->display_texture(this->window_width / 2 - 300, 1020, "green_accept.png", 0.20, 0);
		this->display_texture(this->window_width / 2 + 300, 1020, "red_wrong.png", 0.20, 0);
		this->display_texture(this->window_width / 2, 1020, "red_wrong.png", 0.20, 0);
		if_clear = false;
	}

	this->previos_loop_green_rect_counter = this->green_rect_counter;
	this->green_rect_counter = 0;


	// Sequence
	switch (this->step_of_sequence)
	{
	case 0:
	{
		// Reseting sequence
		data_box.is_sequence_activated = false;

		if (this->sequence_name != data_box.sequence_name)
		{
			data_box.index_and_checked_info_accepted_boxes.clear();

			this->green_rect_counter = 0;
			this->previos_loop_green_rect_counter = 0;
			this->previous_wrong_state = false;
			this->previous_box_writing = 0;
			this->sequence_name = data_box.sequence_name;
		}
		current_step = 0;
		article_installed = false;
		article_taken = false;
		list.clear();
		break;
	}
	case 1: 	// Lighting boxes from witch user takes article
	{
		this->window->draw(this->lighting_rectangles[sequence[current_step].matched_rectangle]);

		int distance = 530;
		for (int i = 0; i < current_step; i++)
		{
			distance = distance + mm_to_pixels_converter(sequence[i].width / 2);
			display_texture(distance, 950, "baza zlaczek/" + std::to_string(sequence[i].serial_number) + ".png", mm_to_pixels_converter(sequence[i].width), mm_to_pixels_converter(sequence[i].height), 0);
			distance = distance + mm_to_pixels_converter(sequence[i].width / 2);
		}

		// Handling 1 -> 2 transition
		if (this->article_taken)
		{
			this->step_of_sequence = 2;
			this->article_taken = false;

			// New element in list
			if(current_step > 0 && current_step < sequence.size() - 1)
				list.erase(list.begin());
			if(sequence.size() > current_step + 1)
				list.push_back(std::to_string(current_step + 2) + "." + std::to_string(1) + " Pobranie " + sequence[current_step + 1].name);
			if (current_step == sequence.size() - 1)
				list.erase(list.begin());
		}
		break;
	}
	case 2:		// Installing article on DIN
	{
		int distance = 530;
		for (int i = 0; i <= current_step; i++)
		{
			distance = distance + mm_to_pixels_converter(sequence[i].width / 2);
			display_texture(distance, 950, "baza zlaczek/" + std::to_string(sequence[i].serial_number) + ".png", mm_to_pixels_converter(sequence[i].width), mm_to_pixels_converter(sequence[i].height), 0);
			distance = distance + mm_to_pixels_converter(sequence[i].width / 2);
		}

		//Handling end of sequence
		if (this->article_installed && current_step + 1 == sequence.size())
		{
			data_box.last_step_of_sequence = true;

			data_box.index_and_checked_info_accepted_boxes.clear();

			this->green_rect_counter = 0;
			this->previos_loop_green_rect_counter = 0;
			this->previous_wrong_state = false;
			this->previous_box_writing = 0;


			this->step_of_sequence = 0;

			this->article_installed = false;
			break; break;
		}
		// Handling 2 -> 1 transition
		else 
		if (this->article_installed)
		{
			// New element in list
			if (current_step > 0 && current_step < sequence.size() - 1)
				list.erase(list.begin());
			if (sequence.size() > current_step + 1)
				list.push_back(std::to_string(current_step + 2) + "." + std::to_string(2) + " Instalacja " + sequence[current_step + 1].name);
			this->step_of_sequence = 1;
			current_step++;
			this->article_installed = false;
			this->actual_length = this->actual_length + sequence[current_step].width;
		}
		break;
	}
	}
	data_box.step_in_sequence = this->step_of_sequence;

	// Drawing
	if (this->step_of_sequence != 0 && if_clear)
	{
		this->display_texture(this->green_button_x, this->green_button_y, "green_circle.png", this->button_size, 0);   //displaying basic graphics 
		this->display_text(this->green_button_x, this->green_button_y + ((this->red_button_length_y*button_size)) / 2, "Kontynuuj", 40); //displaying texts

		for (int i = 0; i < sequence.size(); i++)
			this->display_text(mm_to_pixels_converter(60 + (i * 120)), 600, sequence[i].name, 18);

		if (sequence.size() != 0)
		{
			this->display_text(10, 790, ("Aktualny krok: " + std::to_string(current_step + 1) + "/" + std::to_string(sequence.size())), 46, sf::Color::White);  //displaying "aktualny krok" in corner 		}
		}
		// Drawing sequence list


		if (current_step == 0 && step_of_sequence == 1)
		{
			this->display_text(10, 880, list[0], 30, sf::Color::Yellow);
			this->display_text(10, 930, list[1], 30, sf::Color::Red);
		}
		else if (current_step == 0 && step_of_sequence == 2 && sequence.size() > 1)
		{
			this->display_text(10, 880, list[0], 30, sf::Color::Green);
			this->display_text(10, 930, list[1], 30, sf::Color::Yellow);
			this->display_text(10, 980, list[2], 30, sf::Color::Red);
		}
		else if (current_step == 0 && step_of_sequence == 2 && sequence.size() == 1)
		{
			this->display_text(10, 930, list[0], 30, sf::Color::Yellow);
		}
		else if (current_step == sequence.size() - 1 && step_of_sequence == 2)
		{
			this->display_text(20, 880, list[0], 30, sf::Color::Green);
			this->display_text(10, 930, list[1], 30, sf::Color::Green);
			this->display_text(10, 980, list[2], 30, sf::Color::Yellow);
		}
		else
		{
			this->display_text(10, 880, list[0], 30, sf::Color::Green);
			this->display_text(10, 930, list[1], 30, sf::Color::Green);
			this->display_text(10, 980, list[2], 30, sf::Color::Yellow);
			this->display_text(10, 1030, list[3], 30, sf::Color::Red);
		}

		if (data_box.wrong_box) {
			this->display_texture(this->window_width/2, 750, "red_circlebigger.png", 0.5, 0);
			this->display_text(this->window_width / 2, 850, "Zle pobrany artykul", 40);
		}
		if_clear = false;
	}
	// do testow, przechodzenie do kolejnego kroku na prawy przycisk myszy w window functions

	//data_box.green_button = false;
	//data_box.detecting_box = false;

	//Calibration tape points on table
	if (this->menu_window == 3) {
		sf::RectangleShape rectangle_;
		for (int i = 0; i < this->outline_rectangles.size(); i++) {

			rectangle_.setSize(sf::Vector2f(mm_to_pixels_converter(95), mm_to_pixels_converter(25)));
			rectangle_.setOrigin(sf::Vector2f(rectangle_.getSize().x / 2, rectangle_.getSize().y / 2));
			rectangle_.setPosition(this->outline_rectangles[i].getPosition().x, this->outline_rectangles[i].getPosition().y + this->outline_rectangles[i].getSize().y/2+ mm_to_pixels_converter(25));
			rectangle_.setFillColor(sf::Color::Green);
			
			this->window->draw(rectangle_);
		}
		this->display_text(this->window_width/2, 800, "Jesli jestes pewna/y ze tasmy znajduja sie w podswietlonych na zielono miejscach to zatwierdz na komputerze", 40);
	}
	if (this->menu_window == 301)
	{
		this->display_text(250, 350, "Trwa kalibracja kamery, prosze poczekac:", 75, sf::Color::Black);
		this->display_text(800, 650, std::to_string(this->displayed_time) + " s", 75, sf::Color::Black);
		if_clear = false;
	}

	if (if_display)
		this->window->display();
	if (!if_clear)
		if_display = false;
	else
		if_display = true;
}

