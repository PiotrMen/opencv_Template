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