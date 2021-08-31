#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <mutex>
#include <thread>
#include "csv_read.h"


#ifndef UNIVERSAL_FUNCTIONS_H


// Mutex
extern std::mutex m;
extern std::mutex m2;

// Sequence vector declaration
extern std::vector <sData> sequence;

// Global data
extern sGlobal_data data_box;

//converter return real value in pixels
int mm_to_pixels_converter(float real_mm);

//Detecting sequation ending
bool detecting_sequation_ending();

//universal collision detecting
bool unieversal_detecting_collision_with_buttons(int x, int y, int length_x, int length_y, float scale, sf::RenderWindow *menu_window);

sf::RectangleShape making_rectangle(int pos_x, int pos_y, int size_x, int size_y, sf::Color color, bool setOrigin);

void Universal_display_texture(int pos_x, int pos_y, std::string file_path, float scale, float rotation, sf::RenderWindow *window);
void Universal_display_texture(int pos_x, int pos_y, std::string file_path, float scale, sf::RenderWindow *window);
void Universal_display_text(int pos_x, int pos_y, std::string text, float size, sf::RenderWindow *window); // with default rotation
void Universal_display_text(int pos_x, int pos_y, std::string text, float size, float rotate, int origin_x, int origin_y, sf::RenderWindow *window); // with rotation and origin given by user
void Universal_display_texture_without_origin(int pos_x, int pos_y, std::string file_path, float scale, sf::RenderWindow *window);
float round_float(float input_var, int number_of_decimal_places);

#endif