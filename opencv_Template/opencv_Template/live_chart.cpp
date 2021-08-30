#include "live_chart.h"

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