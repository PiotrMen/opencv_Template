#include "menu_functions.h"
#include <iostream>
#include "articles.h"

//Constructor
menu_sfml_objects::menu_sfml_objects()
{
	this->menu_window_height = 1080;
	this->menu_window_width = 1920;
	this->menu_window = new sf::RenderWindow(sf::VideoMode(menu_window_width, menu_window_height), "Menu", sf::Style::Fullscreen);
	this->menu_window->setPosition(sf::Vector2i(0, -1080));
}

// Initializations
void menu_sfml_objects::init_button_size(float percentege_size, float menu_button_percentege_size)
{
	//length of sides in pixels

	//blue button
	this->blue_button_length_x = 414; // number of pixels (width and length of picture)
	this->blue_button_length_y = 414;

	//coordinates for blue button
	this->blue_button_x = this->menu_window_width - 200;  // 150 - number of pixels from bounds
	this->blue_button_y = this->menu_window_height - 150;

	//length of sides for Select article button
	this->Select_article_length_button_x = 707;
	this->Select_article_length_button_y = 120;

	//coordinates for Select article button
	this->Select_article_button_x = this->menu_window_width / 2;
	this->Select_article_button_y = 400;

	//coordinates for edit article button
	this->edit_article_button_x = this->menu_window_width / 2;
	this->edit_article_button_y = Select_article_button_y + 200;

	//coordinates for delete article button
	this->delete_article_button_x = this->menu_window_width / 2;
	this->delete_article_button_y = edit_article_button_y + 200;

	this->button_size = percentege_size / 100;
	this->menu_button_size = menu_button_percentege_size / 100;
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

bool menu_sfml_objects::detecting_Select_article_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->Select_article_button_x - ((this->Select_article_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->Select_article_button_x + ((this->Select_article_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->Select_article_button_y - ((this->Select_article_length_button_y * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->Select_article_button_y + ((this->Select_article_length_button_y * this->menu_button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_edit_article_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->edit_article_button_x - ((this->Select_article_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->edit_article_button_x + ((this->Select_article_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->edit_article_button_y - ((this->Select_article_length_button_y * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->edit_article_button_y + ((this->Select_article_length_button_y * this->menu_button_size) / 2))))
	{
		return true;
	}
	return false;
}

bool menu_sfml_objects::detecting_delete_article_button()
{
	if (((sf::Mouse::getPosition(*this->menu_window).x >= this->delete_article_button_x - ((this->Select_article_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).x <= this->delete_article_button_x + ((this->Select_article_length_button_x * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y >= this->delete_article_button_y - ((this->Select_article_length_button_y * this->menu_button_size) / 2)) && (sf::Mouse::getPosition(*this->menu_window).y <= this->delete_article_button_y + ((this->Select_article_length_button_y * this->menu_button_size) / 2))))
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
		
			break;
			}

			break;
		}
	}
}

void menu_sfml_objects::update(int &current_step, int &current_window)
{
	this->pollEvents(current_step, current_window);
	if (detecting_Select_article_button() && detecting_falling_edge_left_mouse_button()) {
		current_window = 1;
	}
}


void menu_sfml_objects::render(std::vector <sArticles> &articles, int current_step, int current_window)
{
	this->menu_window->clear(sf::Color(255, 255, 255, 255));

	//Graphics
	this->display_texture(this->blue_button_x, this->blue_button_y, "blue_circle.png", this->button_size, 0);   //displaying basic graphics // 0 if menu displaying, 1 if articles selected

	//Displaying Select button graphics
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_Select_article_button()) {
		this->display_texture(this->Select_article_button_x, this->Select_article_button_y, "grey_pushed.png", this->menu_button_size, 0);

	}
	else
		this->display_texture(this->Select_article_button_x, this->Select_article_button_y, "grey_button.png", this->menu_button_size, 0);

	//Displaying edit button graphics
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_edit_article_button())
		this->display_texture(this->edit_article_button_x, this->edit_article_button_y, "grey_pushed.png", this->menu_button_size, 0);
	else
		this->display_texture(this->edit_article_button_x, this->edit_article_button_y, "grey_button.png", this->menu_button_size, 0);

	//Displaying delete button graphics
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && detecting_delete_article_button())
		this->display_texture(this->delete_article_button_x, this->delete_article_button_y, "grey_pushed.png", this->menu_button_size, 0);
	else
		this->display_texture(this->delete_article_button_x, this->delete_article_button_y, "grey_button.png", this->menu_button_size, 0);


	//Texts
	this->display_text(this->Select_article_button_x, this->Select_article_button_y-10, "Wybor artykulu", 80);
	this->display_text(this->edit_article_button_x, this->edit_article_button_y - 10, "Edycja artykulu", 80);
	this->display_text(this->delete_article_button_x, this->delete_article_button_y - 10, "Usuniecie artykulu", 80);
	this->display_text(this->menu_window_width / 2, 130, "Menu artykulow", 200);

	//UnderLines
	if(detecting_Select_article_button())
		this->display_texture(this->Select_article_button_x, this->Select_article_button_y + 85, "UnderLine.png", this->menu_button_size - 0.2, 0);

	if (detecting_edit_article_button())
		this->display_texture(this->edit_article_button_x, this->edit_article_button_y + 85, "UnderLine.png", this->menu_button_size - 0.2, 0);

	if (detecting_delete_article_button())
		this->display_texture(this->delete_article_button_x, this->delete_article_button_y + 85, "UnderLine.png", this->menu_button_size - 0.2, 0);

	this->menu_window->display();
}

