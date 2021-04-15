#include "header.h"

//Constructor
sfml_objects::sfml_objects()
{
	this->window_height = 1080;
	this->window_width = 1920;
	this->window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), "Window");

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
	texture.setOrigin((texture.getGlobalBounds().left + texture.getGlobalBounds().width)/2, (texture.getGlobalBounds().height + texture.getGlobalBounds().top)/2);         //set origins of images to center
	texture.setPosition(pos_x, pos_y);
	texture.setScale(scale_x, scale_y);


	this->window->draw(texture);
}

//Displaying text
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
	text_.setFont(font_);
	text_.setString(text);
	text_.setCharacterSize(40);
	text_.setOrigin((text_.getGlobalBounds().left + text_.getGlobalBounds().width) / 2, 0);     //set origins of text to center
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


	if (((sf::Mouse::getPosition().x >= this->green_button_x - ((this->green_button_length_x * this->button_size) / 2)) && (sf::Mouse::getPosition().x <= this->green_button_x + ((this->green_button_length_x * this->button_size) / 2)) && (sf::Mouse::getPosition().y >= this->green_button_y - ((this->green_button_length_y * this->button_size) / 2)) && (sf::Mouse::getPosition().y <= this->green_button_y + ((this->green_button_length_y * this->button_size) / 2))))
	{
		return true;
	}
	return false;
}


//Functions
void sfml_objects::pollEvents()
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
				std::cout << "wcisniety" << std::endl;

				switch (event.key.code)
				{
					case sf::Mouse::Left:

						if (this->detecting_green_button())
						{
							std::cout << "lewy wcisniety" << std::endl;
						}
					break;
				}

			break;
		}
	}
}

void sfml_objects::update()
{
	this->pollEvents();
}


void sfml_objects::render()
{
	this->window->clear(sf::Color(255,255,255,255));
	this->display_texture(this->green_button_x, this->green_button_y, "green_circle.png", this->button_size, this->button_size);   //button_size - button scale
	this->display_texture(this->red_button_x, this->red_button_y, "red_circle.png", this->button_size, this->button_size);
	//this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", 0.3, 0.3);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(this->green_button_length_x*this->button_size, this->green_button_length_y*this->button_size));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setOrigin((rectangle.getGlobalBounds().left + rectangle.getGlobalBounds().width) / 2, (rectangle.getGlobalBounds().height + rectangle.getGlobalBounds().top) / 2);
	rectangle.setPosition(this->green_button_x, this->green_button_y);
	this->window->draw(rectangle);

	this->display_text(this->green_button_x, this->green_button_y+((this->red_button_length_y*button_size))/2, "Continue");
	this->display_text(this->red_button_x, this->red_button_y + ((this->red_button_length_y * button_size))/2, "Defect");     // 414 - number of pixels
	this->window->display();
}