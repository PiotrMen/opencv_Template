#include "csv_read.h"

void load_csv_database(std::vector <sData> &articles_in_boxes, std::vector <sData> &left_articles)
{
	std::ifstream file;
	file.open("resources/baza_zlaczek.csv");

	if (file.is_open())
	{
		std::string buffor;

		for(int iterator = 0; std::getline(file, buffor); iterator++)
		{
			sData article;

			// 2 cases
			// 1 - there is "," included in name
			// 2 - there is no "," included in name

			std::smatch match_groups;
			std::regex regex_case_1("([0-9]{7}),\"(.*)\"");
			std::regex regex_case_2("([0-9]{7}),(.*)");

			std::regex_search(buffor, match_groups, regex_case_1);
			if (match_groups[0] == "")
			{
				std:regex_search(buffor, match_groups, regex_case_2);
			}
			article.serial_number = stoi(match_groups[1]);
			article.name = match_groups[2];

			if (iterator < 10)
			{
				articles_in_boxes.push_back(article);
			}
			else
			{
				left_articles.push_back(article);
			}
			//articles.push_back(article);
		}
	}
	file.close();
}

void save_csv_database(const std::vector <sData> &articles_in_boxes, const std::vector <sData> &left_articles)
{
	std::ofstream file;
	file.open("resources/baza_zlaczek.csv");

	if (file.is_open())
	{
		for (int i = 0; i < articles_in_boxes.size(); i++)
		{
			file << i + 1 << "," << articles_in_boxes[i].serial_number << ",";

			// Searching if name has ","
			size_t searching_point = articles_in_boxes[i].name.find(",");

			if (searching_point != 0)
			{
				file << "\"" << articles_in_boxes[i].name << "\"\n";
			}
			else
			{
				file << articles_in_boxes[i].name << "\n";
			}
		}
		for (int i = 0; i < left_articles.size(); i++)
		{
			file << i + 21 << "," << left_articles[i].serial_number << ",";

			// Searching if name has ","
			size_t searching_point = left_articles[i].name.find(",");

			if (searching_point != 0)
			{
				file << "\"" << left_articles[i].name << "\"\n";
			}
			else
			{
				file << left_articles[i].name << "\n";
			}
		}
	}
	file.close();
}

void load_csv_sequence(std::vector <sData> &sequence, std::string file_name, std::vector <sData> &connectors_list)
{
	std::ifstream file;
	file.open("resources/" + file_name + ".csv");

	if (file.is_open())
	{
		std::string buffor;

		std::getline(file, buffor);

		while(std::getline(file, buffor))
		{
			sData article;

			// 2 cases
			// 1 - there is "," included in name
			// 2 - there is no "," included in name

			std::smatch match_groups;
			std::regex regex_case_1("([0-9]{7}),\"(.*)\",([0-9]*),(([0-9]*)|\"([0 - 9], [0 - 9])\"),(([0-9]*)|\"([0 - 9], [0 - 9])\")");
			std::regex regex_case_2("([0-9]{7}),(.*),([0-9]*),(([0-9]*)|\"([0 - 9], [0 - 9])\"),(([0-9]*)|\"([0 - 9], [0 - 9])\")");

			std::regex_search(buffor, match_groups, regex_case_1);
			if (match_groups[0] == "")
			{
			std:regex_search(buffor, match_groups, regex_case_2);
			}


			article.serial_number = stoi(match_groups[1]);
			article.name = match_groups[2];
			article.quantity = stoi(match_groups[3]);
			article.width = stof(match_groups[4]);
			article.height = stof(match_groups[7]);

			sequence.push_back(article);
		}
	}
	file.close();

	// Generating unique connectors list

	generate_connectors_list(sequence, connectors_list);

	// Checking if sequence can be performed

	if (connectors_list.size() > 10) // Sequence can not be performed
	{
		connectors_list.clear();
		sequence.clear();
	}
}

void generate_connectors_list(const std::vector <sData> &sequence, std::vector <sData> &connectors_list)
{
	bool repeated = false;
	for (int i = 0; i < sequence.size(); i++)
	{
		for (int k = 0; k < connectors_list.size(); k++)
		{
			if (sequence[i].serial_number == connectors_list[k].serial_number)
			{
				repeated = true;
			}
		}
		if (repeated == false)
		{
			connectors_list.push_back(sequence[i]);
		}
		repeated = false;
	}
}

std::string load_txt_help(std::string filename)
{
	std::ifstream file;
	file.open("resources/" + filename);

	if (file.is_open())
	{
		std::string output_text;
		std::string line;
		while (getline(file, line))
		{
			output_text = output_text + line + "\n";
			line = "";
		}
		file.close();
		return output_text;
	}
	else
	{
		file.close();
		return "Nie mozna odczytac pliku";
	}
}

void load_table_coordinates(std::vector <cv::Point> &points)
{
	std::ifstream file;
	file.open("resources/Zapisane wspolrzedne stolu.txt");
	points.clear();

	if (file.is_open())
	{
		std::string buffor;

		std::getline(file, buffor);
		std::getline(file, buffor);

		for (int i = 0; i < 4; i++)
		{
			cv::Point temporary_point;

			std::getline(file, buffor);

			std::smatch match_coordinates;
			std::regex pattern("\(([0-9]*),([0-9]*)\)");

			std::regex_search(buffor, match_coordinates, pattern);

			temporary_point.x = std::stoi(match_coordinates[2]);
			temporary_point.y = std::stoi(match_coordinates[3]);
			points.push_back(temporary_point);
		}
	}
	file.close();
}
void save_table_coordinates(std::vector <cv::Point> points)
{
	std::ofstream file;
	file.open("resources/Zapisane wspolrzedne stolu.txt");
	std::string readme = "Niniejszy plik s³u¿y do przechowywania wartoœci wspó³rzêdnych sto³u, które zapisane zosta³y po ukoñczeniu poprzedniej kalibracji. Nie zaleca siê edytowania wartoœci rêcznie. W celu przekalibrowania systemu, nale¿y go uruchomiæ, klikn¹æ przycisk \"Kalibracja systemu\" a nastêpnie wykonywaæ wyœwietlane instrukcje.";

	if (file.is_open())
	{
		file << readme << std::endl;
		file << std::endl;
		for (int i = 0; i < 4; i++)
		{
			file << "(" << std::to_string(points[i].x) << "," << std::to_string(points[i].y) << ")" << std::endl;
		}
	}
	file.close();
}