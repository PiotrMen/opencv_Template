#include "Universal_functions.h"
#include <cmath>
#include <SFML/Graphics.hpp>

//converter return real value in pixels
int mm_to_pixels_converter(float Window_width , float Working_field, float real_mm){
	float converter = Window_width / Working_field;
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

void display_rectangle(int pos_x, int pos_y, int size_x, int size_y, sf::Color color,sf::RenderWindow &Window)
{
	sf::RectangleShape rectangle_;
	rectangle_.setSize(sf::Vector2f(size_x, size_y));
	rectangle_.setOrigin(sf::Vector2f(rectangle_.getSize().x / 2, rectangle_.getSize().y / 2));
	rectangle_.setPosition(pos_x, pos_y);
	rectangle_.setOutlineColor(sf::Color::Green);

	Window.draw(rectangle_);
}