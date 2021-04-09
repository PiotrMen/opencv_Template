#include "header.h"

//Constructor
sfml_objects::sfml_objects()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Window");

}

// Initializations
void sfml_objects::init_button_size(int percentege_size)
{
	//coordinates for green button
	this->green_button_x = 1696;
	this->green_button_y = 856;

	//coordinates for red button
	this->red_button_x = 100;
	this->red_button_y = 856;

	//coordinates for blue button
	this->blue_button_x = 0;
	this->blue_button_y = 0;
}

//Displaying objects
void sfml_objects::display_texture(int pos_x, int pos_y, std::string file_path, float scale_x, float scale_y)
{
	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/" + file_path))
	{
		std::cerr << "Could not load texture" << std::endl;
		exit(1);
	}
	sf::Sprite texture;
	texture.setTexture(texture_);
	texture.setPosition(pos_x, pos_y);
	texture.setScale(scale_x, scale_y);


	this->window->draw(texture);
}

void sfml_objects::display_text(int pos_x, int pos_y, std::string text)
{
	sf::Font font_;
	if (!font_.loadFromFile("resources/mermaid/Mermaid1001.ttf"))
	{
		std::cerr << "Could not load font" << std::endl;
		exit(1);
	}
	sf::Text text_;
	text_.setFillColor(sf::Color::Black);
	text_.setPosition(pos_x, pos_y);
	text_.setFont(font_);
	text_.setString(text);
	text_.setCharacterSize(40);
	
	this->window->draw(text_);
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
	this->display_texture(this->green_button_x, this->green_button_y, "green_circle.png", 0.3, 0.3);
	this->display_texture(this->red_button_x, this->red_button_y, "red_circle.png", 0.3, 0.3);
	//this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", 0.3, 0.3);
	this->display_text(this->green_button_x, this->green_button_y, "Continue");
	this->window->display();
}