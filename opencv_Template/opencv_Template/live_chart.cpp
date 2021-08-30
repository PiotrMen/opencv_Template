#include "live_chart.h"

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

void cLive_chart::update(int &current_menu_window, bool &if_clear, bool &if_display, sf::RenderWindow *menu_window) {

	this->rising_edge_saved = detecting_rising_edge_left_mouse_button();
	this->falling_edge_saved = detecting_falling_edge_left_mouse_button();
	this->current_menu_window = current_menu_window;
	this->if_clear = if_clear;
	this->if_display = if_display;

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

void cLive_chart::render(sf::RenderWindow *menu_window) {

	//Live charts section
	if (this->current_menu_window == 203 && this->if_clear) {

		if (if_clear)
			menu_window->clear(sf::Color(255, 255, 255, 255));

		Live_chart_display_texture(71, 796, "menu/axis.png", 0.2, menu_window);

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

		this->if_clear = false;

		if (if_display)
			menu_window->display();
		if (!if_clear)
			if_display = false;
		else
			if_display = true;
	}
}