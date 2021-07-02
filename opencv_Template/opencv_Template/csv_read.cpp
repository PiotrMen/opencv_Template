#include "csv_read.h"

void load_data(std::vector <sData> &articles)
{
	std::ifstream file;
	file.open("resources/baza_zlaczek.csv");

	if (file.is_open())
	{
		std::string buffor;

		while (std::getline(file, buffor))
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
			articles.push_back(article);
		}
	}

	file.close();
}