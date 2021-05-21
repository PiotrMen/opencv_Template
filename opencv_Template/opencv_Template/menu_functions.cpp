#include "menu_functions.h"
#include <iostream>
#include "articles.h"

//Constructor
menu_sfml_objects::menu_sfml_objects()
{
	this->menu_window_height = 1080;
	this->menu_window_width = 1920;
	this->menu_window = new sf::RenderWindow(sf::VideoMode(menu_window_width, menu_window_height), "Menu", sf::Style::Fullscreen);

}

// Initializations
void menu_sfml_objects::init_button_size(float percentege_size)
{
	//length of sides in pixels

	//blue button
	this->blue_button_length_x = 414; // number of pixels (width and length of picture)
	this->blue_button_length_y = 414;

	//coordinates for green button
	this->blue_button_x = this->menu_window_width - 150 - ((this->blue_button_length_x / 2) * percentege_size / 100);  // 150 - number of pixels from bounds
	this->blue_button_y = this->menu_window_height - 150 - ((this->blue_button_length_y / 2) * percentege_size / 100);

	this->button_size = percentege_size / 100;
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
	//std::cout << "myszka x  " << sf::Mouse::getPosition(*this->window).x << "  " << sf::Mouse::getPosition(*this->window).y << std::endl;
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
	text_.setOrigin((text_.getGlobalBounds().left + text_.getGlobalBounds().width) / 2, 0);     //set origins of text to center
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



//Functions
void menu_sfml_objects::pollEvents(int &current_step, int &current_window)
{
	//Event polling
	while (this->menu_window->pollEvent(this->event))
	{
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
			break;
		case sf::Event::MouseButtonPressed:

			switch (event.key.code)
			{
			case sf::Mouse::Left:
				if (current_window == 0) {
					if (this->detecting_blue_button())
					{
						std::cout << "niebieski przycisk" << std::endl;
					}
				}
				break;
			}

			break;
		}
	}
}

void menu_sfml_objects::update(int &current_step, int &current_window)
{
	this->pollEvents(current_step, current_window);
}


void menu_sfml_objects::render(std::vector <sArticles> &articles, int current_step, int current_window)
{
	this->menu_window->clear(sf::Color(255, 255, 255, 255));
	this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", this->button_size, 0);   //displaying basic graphics 
	this->menu_window->display();
}
