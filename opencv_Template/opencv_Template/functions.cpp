#include "header.h"

//Constructor
sfml_objects::sfml_objects()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Window");
	this->green_button_x = 0;
	this->green_button_y = 0;
}

//Displaying objects
void sfml_objects::display_next_button(int pos_x, int pos_y)
{
	sf::Texture green_button_;
	if (!green_button_.loadFromFile("resources/NBA.jpg"))
	{
		std::cerr << "Could not load texture" << std::endl;
		exit(1);
	}
	sf::Sprite sGreen_button;
	sGreen_button.setTexture(green_button_);
	sGreen_button.setPosition(pos_x, pos_y);

	this->window->draw(sGreen_button);
}

//Accessors
const bool sfml_objects::getWindowIsOpen()
{
	return this->window->isOpen();
}

//Functions
void sfml_objects::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->event))
	{

	}
}

void sfml_objects::update()
{
	this->pollEvents();
}

void sfml_objects::render()
{
	this->window->clear(sf::Color(255,255,255,255));
	this->display_next_button(this->green_button_x, this->green_button_y);
	this->window->display();
}