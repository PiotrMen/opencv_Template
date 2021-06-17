#include "window_functions_.h"
#include <iostream>
#include "articles.h"

//Constructor
sfml_objects::sfml_objects()
{
	this->window_height = 1080;
	this->window_width = 1920;
	this->window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), "Window", sf::Style::Fullscreen);

}

// Initializations
void sfml_objects::init_button_size(float percentege_size)
{
	//length of sides in pixels

	//green button
	this->green_button_length_x = 414; // number of pixels (width and length of picture)
	this->green_button_length_y = 414;

	//coordinates for green button
	this->green_button_x = this->window_width - 150 - ((this->green_button_length_x / 2) * percentege_size / 100);  // 150 - number of pixels from bounds
	this->green_button_y = this->window_height - 150 - ((this->green_button_length_y / 2) * percentege_size / 100);

	//red button
	this->red_button_length_x = 414;
	this->red_button_length_y = 414;

	//coordinates for red button
	this->red_button_x = 150 + ((this->red_button_length_x / 2) * percentege_size / 100);
	this->red_button_y = this->window_height - 150 - ((this->red_button_length_y / 2) * percentege_size / 100);


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
	//std::cout << "myszka x  " << sf::Mouse::getPosition(*this->window).x << "  " << sf::Mouse::getPosition(*this->window).y << std::endl;
	texture.setScale(scale, scale);
	texture.setRotation(rotation);

	this->window->draw(texture);
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
	text_.setFillColor(sf::Color::Black);
	text_.setFont(font_);
	text_.setString(text);
	text_.setCharacterSize(size);
	text_.setOrigin((text_.getGlobalBounds().left + text_.getGlobalBounds().width) / 2, 0);     //set origins of text to center
	text_.setPosition(pos_x, pos_y);
	this->window->draw(text_);
}

//Displaying rectangles (based on .txt file)
void sfml_objects::display_rectangle(int pos_x, int pos_y, int size_x, int size_y, float rotation)
{
	sf::RectangleShape rectangle_;
	rectangle_.setSize(sf::Vector2f(size_x, size_y));
	rectangle_.setOrigin(sf::Vector2f(rectangle_.getSize().x / 2, rectangle_.getSize().y / 2));
	rectangle_.setPosition(pos_x, pos_y);
	rectangle_.setOutlineColor(sf::Color::Green);
	rectangle_.setOutlineThickness(20);
	rectangle_.setRotation(rotation);

	this->window->draw(rectangle_);
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
void sfml_objects::pollEvents(int &current_step, int &current_window)
{
	//Event polling
	while (this->window->pollEvent(this->event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				this->window->close();
			break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					this->window->close();
				}
			break;
			case sf::Event::MouseButtonPressed:

				switch (event.key.code)
				{
					case sf::Mouse::Left:
						//article choosen, displaying sequence
						if (current_window == 1) {                           
							if (this->detecting_green_button())
							{
								std::cout << "zielony przycisk" << std::endl;
								current_step++;
							}

							if (this->detecting_red_button())
							{
								current_window = 0;
							}
						}
					break;
				}

			break;
		}
	}
}

void sfml_objects::update(int &current_step, int &current_window)
{
	this->pollEvents(current_step, current_window);
}


void sfml_objects::render(std::vector <sArticles> &articles, int current_step, int current_window)
{
	this->window->clear(sf::Color(255,255,255,255));
	if (current_window == 1) {
		this->display_texture(this->green_button_x, this->green_button_y, "green_circle.png", this->button_size, 0);   //displaying basic graphics 
		this->display_texture(this->red_button_x, this->red_button_y, "red_circle.png", this->button_size, 0);
		this->display_text(this->green_button_x, this->green_button_y + ((this->red_button_length_y*button_size)) / 2, "Continue", 40); //displaying texts
		this->display_text(this->red_button_x, this->red_button_y + ((this->red_button_length_y * button_size)) / 2, "Defect", 40);
		this->display_text(1700, 50, ("Aktualny krok: " + std::to_string(current_step) + "/" + std::to_string(articles[0].number_of_steps)), 40);  //displaying "aktualny krok" in corner
		//	Displaying current step

		if (current_step <= articles[0].number_of_steps && current_step > 0)
		{
			for (int i = 0; i < articles[0].pictures[current_step - 1].size(); i++) {
				this->display_texture(articles[0].coordinates_of_pictures[current_step - 1][i].first, articles[0].coordinates_of_pictures[current_step - 1][i].second, articles[0].pictures[current_step - 1][i], articles[0].scale_of_pictures[current_step - 1][i], articles[0].rotation_of_pictures[current_step - 1][i]);
			}
		}
	}
	// sprawdzanie i przechodzenie do kolejnego kroku, pozniej bedzie zawierac detekcje

	//this->pollEvents(current_step);

	this->window->display();
}

