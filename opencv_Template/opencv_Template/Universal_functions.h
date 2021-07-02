#pragma once
#include <SFML/Graphics.hpp>
#ifndef UNIVERSAL_FUNCTIONS_H

//converter return real value in pixels
int mm_to_pixels_converter(float Window_width, float working_field ,float real_mm);

//universal collision detecting
bool unieversal_detecting_collision_with_buttons(int x, int y, int length_x, int length_y, float scale, sf::RenderWindow *menu_window);

void display_rectangle(int pos_x, int pos_y, int size_x, int size_y, sf::Color color,sf::RenderWindow &Window);

#endif