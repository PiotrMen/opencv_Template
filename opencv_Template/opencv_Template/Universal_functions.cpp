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

void Universal_display_texture_without_origin(int pos_x, int pos_y, std::string file_path, float scale, sf::RenderWindow *window)
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
		texture.setPosition(pos_x, pos_y);
		texture.setScale(scale, scale);

		window->draw(texture);
	}
}

//Displaying text
void Universal_display_text(int pos_x, int pos_y, std::string text, float size, sf::RenderWindow *window)
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
	window->draw(text_);
}
void Universal_display_text(int pos_x, int pos_y, std::string text, float size, float rotate, int origin_x, int origin_y, sf::RenderWindow *window)
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
	text_.setRotation(rotate);
	text_.setOrigin(origin_x, origin_y);     //set origins of text to center
	text_.setPosition(pos_x, pos_y);
	window->draw(text_);
}
float round_float(float input_var, int number_of_decimal_places)
{
	int converter = pow(10, number_of_decimal_places);
	float output_var = (int)(input_var * converter + 0.5);
	output_var = (float)(output_var / converter);

	return output_var;
}

void Universal_display_text_polish_font(int pos_x, int pos_y, std::wstring text, float size, float rotate, sf::RenderWindow *window) {
	sf::Font font_;
	if (!font_.loadFromFile("resources/mermaid/AbhayaLibre-Regular.ttf"))
	{
		std::cerr << "Could not load font" << std::endl;
		exit(1);
	}
	sf::Text text_;
	text_.setFillColor(sf::Color::Black);
	text_.setFont(font_);
	text_.setString(text);
	text_.setCharacterSize(size);
	text_.setRotation(rotate);
	text_.setOrigin((text_.getGlobalBounds().left + text_.getGlobalBounds().width) / 2, (text_.getGlobalBounds().height + text_.getGlobalBounds().top) / 2);     //set origins of text to center
	text_.setPosition(pos_x, pos_y);
	window->draw(text_);
}

// convert UTF-8 string to wstring
std::wstring String_to_wString(const std::string & s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}