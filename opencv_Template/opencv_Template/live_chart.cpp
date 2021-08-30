#include "live_chart.h"

cLive_chart::cLive_chart(int pos_x, int pos_y, int size) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->size = size;
	this->coefficient = 0.893;
	this->first_bar = (170 + 83) / 769.0;
	this->second_bar =(320 + 83) / 769.0;
	this->third_bar = (470 + 83) / 769.0;
	this->fourth_bar = (620 + 83)/ 769.0;
}

 bool cLive_chart::detecting_rising_edge(bool signal) {
	if (this->rising_edge_signal == false && signal) {
		this->rising_edge_detected_signal = true;
	}
	else {
		this->rising_edge_signal = false;
	}
	if (signal) {
		this->rising_edge_signal = true;
	}
	if (this->rising_edge_detected_signal) {
		this->rising_edge_detected_signal = false;
		return true;
	}
	return false;
}

bool cLive_chart::detecting_falling_edge(bool signal) {
	if (this->falling_edge_signal == true && !signal) {
		this->falling_edge_detected_signal = true;
		this->falling_edge_signal = false;
	}
	if (signal) {
		this->falling_edge_signal = true;
	}
	if (this->falling_edge_detected_signal) {
		this->falling_edge_detected_signal = false;
		this->falling_edge_signal = false;
		return true;
	}
	return false;
}

bool cLive_chart::detecting_rising_edge_left_mouse_button() {
	if (this->rising_edge == false && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->rising_edge_detected = true;
	}
	else {
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

bool cLive_chart::detecting_falling_edge_left_mouse_button() {
	if (this->falling_edge == true && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->falling_edge_detected = true;
		this->falling_edge = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->falling_edge = true;
	}
	if (this->falling_edge_detected) {
		this->falling_edge_detected = false;
		this->falling_edge = false;
		return true;
	}
	return false;
}


void cLive_chart::load_statistics()
{
	std::ifstream file;
	file.open("resources/Statystyki.csv");

	if (file.is_open())
	{
		std::string buffor;

		// Reading "Statystyki"
		std::getline(file, buffor);
		// Reading max time
		std::getline(file, buffor);
		std::getline(file, buffor);

		std::smatch match_times;
		std::regex pattern("\"([0-9]*,[0-9]*)\"|([0-9]*)");

		std::regex_search(buffor, match_times, pattern);
		std::string stof_converter;
		if (match_times[1].matched != false)
		{
			stof_converter = match_times[1];
			std::replace(stof_converter.begin(), stof_converter.end(), ',', '.');
		}
		else
			stof_converter = match_times[2];

		this->max_sequence_time = stof(stof_converter);

		// Reading min time
		std::getline(file, buffor);
		std::getline(file, buffor);

		std::regex_search(buffor, match_times, pattern);
		if (match_times[1].matched != false)
		{
			stof_converter = match_times[1];
			std::replace(stof_converter.begin(), stof_converter.end(), ',', '.');
		}
		else
			stof_converter = match_times[2];
		this->min_sequence_time = stof(stof_converter);

		// Reading oldest time iterator
		std::getline(file, buffor);
		std::getline(file, buffor);
		this->oldest_time_recorded_iterator = std::stoi(buffor);

		std::getline(file, buffor);
		// Reading times
		while (std::getline(file, buffor))
		{
			std::regex_search(buffor, match_times, pattern);
			if (match_times[1].matched != false)
			{
				stof_converter = match_times[1];
				std::replace(stof_converter.begin(), stof_converter.end(), ',', '.');
			}
			else
				stof_converter = match_times[2];
			this->sequence_times.push_back(stof(stof_converter));
		}

	}
	file.close();
}
void cLive_chart::save_statistics()
{
	std::ofstream file;
	file.open("resources/Statystyki.csv");

	if (file.is_open())
	{
		file << "Statystyki:" << std::endl;
		file << "Czas maksymalny:" << std::endl;

		std::string ftos_converter = std::to_string(this->max_sequence_time);

		if (std::find(ftos_converter.begin(), ftos_converter.end(), '.') != ftos_converter.end())
		{
			std::replace(ftos_converter.begin(), ftos_converter.end(), '.', ',');
			ftos_converter = '\"' + ftos_converter + '\"';
		}
		file << ftos_converter << std::endl;

		file << "Czas minimalny:" << std::endl;
		ftos_converter = std::to_string(this->min_sequence_time);

		if (std::find(ftos_converter.begin(), ftos_converter.end(), '.') != ftos_converter.end())
		{
			std::replace(ftos_converter.begin(), ftos_converter.end(), '.', ',');
			ftos_converter = '\"' + ftos_converter + '\"';
		}
		file << ftos_converter << std::endl;

		file << "Pozycja najstarszego rekordu:" << std::endl;
		file << std::to_string(this->oldest_time_recorded_iterator) <<std::endl;

		file << "Czasy sekwencji:" << std::endl;

		for (int i = 0; i < this->sequence_times.size(); i++)
		{
			ftos_converter = std::to_string(this->sequence_times[i]);

			if (std::find(ftos_converter.begin(), ftos_converter.end(), '.') != ftos_converter.end())
			{
				std::replace(ftos_converter.begin(), ftos_converter.end(), '.', ',');
				ftos_converter = '\"' + ftos_converter + '\"';
			}
			file << ftos_converter << std::endl;
		}
	}
	file.close();
}

void cLive_chart::add_new_time(float new_time)
{
	// Checking if new time is greater than max or lesser than min

	if (new_time < this->min_sequence_time)
		this->min_sequence_time = new_time;
	if (new_time > this->max_sequence_time)
		this->max_sequence_time = new_time;

	// Adding time to the list
	// Checking if list is greater then 10 000. If so, overwrite oldest time
	if (this->sequence_times.size() >= 10000)
	{
		this->sequence_times[this->oldest_time_recorded_iterator] = new_time;
		if (this->oldest_time_recorded_iterator == 9999)
			this->oldest_time_recorded_iterator = 0;
		else
			this->oldest_time_recorded_iterator++;

	}
	else
	{
		sequence_times.push_back(new_time);
	}

	this->time_mean_value = 0;
	for (int i = 0; i < this->sequence_times.size(); i++)
		this->time_mean_value = this->time_mean_value + this->sequence_times[i];
	this->time_mean_value = this->time_mean_value / this->sequence_times.size();
}

void cLive_chart::Live_chart_axis_display(std::string file_path, sf::RenderWindow *window)
{
	//This function displays objects that are not guaranteed to exist
	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/menu/" + file_path))
	{
	}
	else
	{
		sf::Sprite texture;
		texture.setTexture(texture_);
		this->scale = this->size / texture.getGlobalBounds().width;
		texture.setPosition(this->pos_x, this->pos_y);
		texture.setScale(scale, scale);
		this->image_size = texture.getGlobalBounds().width;

		window->draw(texture);
	}
}

void cLive_chart::Live_chart_bars_display(int pos_x, int pos_y, std::string file_path, float time_scale,sf::RenderWindow *window)
{
	//This function displays objects that are not guaranteed to exist
	sf::Texture texture_;
	if (!texture_.loadFromFile("resources/menu/" + file_path))
	{
	}
	else
	{
		sf::Sprite texture;
		texture.setTexture(texture_);
		texture.setOrigin(sf::Vector2f(2*texture.getTexture()->getSize().x, texture.getTexture()->getSize().y));         //set origins of images to center
		texture.setPosition(pos_x, pos_y+1);

		texture.setScale(this->scale*0.5, this->scale * time_scale);

		window->draw(texture);
	}
}

void cLive_chart::update(int &current_menu_window, bool &if_clear, bool &if_display, sf::RenderWindow *menu_window) {

	this->if_active = true;
	this->rising_edge_saved = detecting_rising_edge_left_mouse_button();
	this->falling_edge_saved = detecting_falling_edge_left_mouse_button();
	this->current_menu_window = current_menu_window;

	this->calculating_bars();


	if (data_box.is_sequence_activated == false)
		this->sequence_clock.restart();
	else
		this->time_of_sequence = this->sequence_clock.getElapsedTime();


	if (current_menu_window == 203) {
		//start window clear if mouse is on display live charts button
		if ((rising_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, menu_window)) || (falling_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, menu_window))) {
			if_clear = true;
			if_display = true;
		}
		//start window clear underline on display live charts button
		if (detecting_falling_edge(unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, menu_window) && current_menu_window == 203) || (detecting_rising_edge(unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, menu_window) && current_menu_window == 203))) {
			if_clear = true;
			if_display = true;
		}
		//backing to 202
		if ((this->previous_current_menu_window == current_menu_window) && (falling_edge_saved && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, menu_window))) {
			current_menu_window = 202;
			if_clear = true;
			if_display = true;
		}
		this->previous_current_menu_window = current_menu_window;
	}
}

void cLive_chart::render(bool &if_clear, bool &if_display, sf::RenderWindow *menu_window) {

	//Live charts section
	if (this->current_menu_window == 203 && if_clear) {

		if (if_clear)
			menu_window->clear(sf::Color(255, 255, 255, 255));

		this->Live_chart_axis_display("axis.png", menu_window);
		this->Live_chart_bars_display(this->image_size*this->first_bar+this->pos_x, this->image_size*this->coefficient+this->pos_y, "pink_column.png",this->scale_max, menu_window);
		this->Live_chart_bars_display(this->image_size*this->second_bar + this->pos_x, this->image_size*this->coefficient + this->pos_y, "Blue_column.png", this->scale_min, menu_window);
		this->Live_chart_bars_display(this->image_size*this->third_bar + this->pos_x, this->image_size*this->coefficient + this->pos_y, "yellow_column.png", this->scale_mean, menu_window);
		this->Live_chart_bars_display(this->image_size*this->fourth_bar + this->pos_x, this->image_size*this->coefficient + this->pos_y, "green_column.png", this->scale_present, menu_window);

		//display back to 202
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, menu_window)) {
			Universal_display_texture(960, 950, "menu/grey_pushed.png", data_box.menu_button_size, 0, menu_window);
			Universal_display_text(960, 935, "Wyswietl wykresy", 100, menu_window);
		}
		else {
			Universal_display_texture(960, 950, "menu/grey_button.png", data_box.menu_button_size, 0, menu_window);
			Universal_display_text(960, 935, "Wyswietl wykresy", 100, menu_window);
		}
		if (unieversal_detecting_collision_with_buttons(960, 950, data_box.Upload_file_length_button_x, data_box.Upload_file_length_button_y, data_box.menu_button_size, menu_window))
			Universal_display_texture(960, 950 + 85, "menu/UnderLine.png", data_box.menu_button_size - 0.2, 0, menu_window);

		if_clear = false;

		if (if_display)
			menu_window->display();
		if (!if_clear)
			if_display = false;
		else
			if_display = true;
	}
}
void cLive_chart::calculating_bars()
{
	// Zmienne do przypisania pozniej

	float max_height = (this->size*this->coefficient)-100;
	float x = 200; // Wysokosc obrazka przed przeskalowaniem
	
	// if max_sequence_time is longest
	if (this->max_sequence_time >= this->min_sequence_time && this->max_sequence_time >= this->time_mean_value && this->max_sequence_time >= this->present_time)
	{
		this->scale_max = max_height / x;

		// Calculating min time bar height
		this->scale_min = (this->min_sequence_time / this->max_sequence_time) * max_height / x;

		// Calculating average time bar height
		this->scale_mean = (this->time_mean_value / this->max_sequence_time) * max_height / x;

		// Calculating present time bar height
		this->scale_present = (this->present_time / this->max_sequence_time) * max_height / x;

	}
	// if min_sequence_time is longest
	else if (this->min_sequence_time >= this->max_sequence_time && this->min_sequence_time >= this->time_mean_value && this->min_sequence_time >= this->present_time)
	{
		this->scale_min = max_height / x;

		// Calculating max time bar height
		this->scale_max = this->max_sequence_time / this->min_sequence_time * max_height / x;

		// Calculating average time bar height
		this->scale_mean = this->time_mean_value / this->min_sequence_time * max_height / x;

		// Calculating present time bar height
		this->scale_present = this->present_time / this->min_sequence_time * max_height / x;
	}
	// if mean value is longest
	else if (this->time_mean_value >= this->min_sequence_time && this->time_mean_value >= this->max_sequence_time && this->time_mean_value >= this->present_time)
	{
		this->scale_mean = max_height / x;

		// Calculating max time bar height
		this->scale_max = this->max_sequence_time / this->time_mean_value * max_height / x;

		// Calculating average time bar height
		this->scale_min = this->min_sequence_time / this->time_mean_value * max_height / x;

		// Calculating present time bar height
		this->scale_present = this->present_time / this->time_mean_value * max_height / x;
	}
	// if present time is longest
	else if (this->present_time >= this->min_sequence_time && this->present_time >= this->max_sequence_time && this->present_time >= this->time_mean_value)
	{
		this->scale_present = max_height / x;

		// Calculating max time bar height
		this->scale_max = this->max_sequence_time / this->present_time * max_height / x;

		// Calculating average time bar height
		this->scale_min = this->min_sequence_time / this->present_time * max_height / x;

		// Calculating present time bar height
		this->scale_mean = this->time_mean_value / this->present_time * max_height / x;
	}

}