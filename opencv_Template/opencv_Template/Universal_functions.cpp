#include "Universal_functions.h"
#include <cmath>
#include <SFML/Graphics.hpp>

//converter return real value in pixels
int mm_to_pixels_converter(float real_mm){
	float converter = 1920.0 / 1200.0;
	float result_in_pixels = real_mm * converter;
	return (int) round(result_in_pixels);
}

//universal collision detecting
bool unieversal_detecting_collision_with_buttons(int x, int y, int length_x, int length_y, float scale, sf::RenderWindow *menu_window) {
	if (((sf::Mouse::getPosition(*menu_window).x >= x - ((length_x * scale) / 2)) && (sf::Mouse::getPosition(*menu_window).x <= x + ((length_x * scale) / 2)) && (sf::Mouse::getPosition(*menu_window).y >= y - ((length_y * scale) / 2)) && (sf::Mouse::getPosition(*menu_window).y <= y + ((length_y * scale) / 2))))
	{
		return true;
	}
	return false;
}

sf::RectangleShape making_rectangle(int pos_x, int pos_y, int size_x, int size_y, sf::Color color, bool setOrigin)
{
	sf::RectangleShape rectangle_;
	rectangle_.setSize(sf::Vector2f(size_x, size_y));
	if(setOrigin)
		rectangle_.setOrigin(0, rectangle_.getSize().y / 2);
	else
		rectangle_.setOrigin(sf::Vector2f(rectangle_.getSize().x / 2, rectangle_.getSize().y / 2));
	rectangle_.setPosition(pos_x, pos_y);
	rectangle_.setFillColor(color);
	
	return(rectangle_);
}
	
//Detecting sequation ending
bool detecting_sequation_ending() {
	if (data_box.boxes.size() != 0 && !data_box.is_sequence_activated && data_box.last_step_of_sequence)
		return true;
	else
		return false;
}

void Universal_display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation, sf::RenderWindow *window)
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

	window->draw(texture);
}
void Universal_display_texture(int pos_x, int pos_y, std::string file_path, float scale, sf::RenderWindow *window)
{
	//This function displays objects that are not guaranteed to exist
	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/" + file_path))
	{
	}
	else
	{
		sf::Sprite texture;
		texture.setTexture(texture_);
		texture.setOrigin(sf::Vector2f(texture.getTexture()->getSize().x * 0.5, texture.getTexture()->getSize().y * 0.5));         //set origins of images to center
		texture.setPosition(pos_x, pos_y);
		texture.setScale(scale, scale);

		window->draw(texture);
	}
}
void Live_chart_display_texture(int pos_x, int pos_y, std::string file_path, float scale, sf::RenderWindow *window)
{
	//This function displays objects that are not guaranteed to exist
	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/" + file_path))
	{
	}
	else
	{
		sf::Sprite texture;
		texture.setTexture(texture_);
		texture.setOrigin(sf::Vector2f(texture.getPosition().x+71, texture.getTexture()->getSize().y-71));         //set origins of images to center
		texture.setPosition(pos_x, pos_y);
		texture.setScale(scale, scale);

		window->draw(texture);
	}
}