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
	if (data_box.boxes.size() != 0 && !data_box.is_sequence_activated)
		return true;
	else
		return false;
}