#include "structures.h"
#include <regex>

void load_articles(sArticles &adding_article)
{
	std::ifstream file;
	file.open("resources/articles.txt");
	int step_of_article = 0;
	std::vector<std::string> steps;

	if (file.is_open())
	{
		//adding article name
		while (std::getline(file, adding_article.name)){
			
			step_of_article = 0;
		//adding article number of steps
			std::string number_of_steps;
			std::getline(file, number_of_steps);
			adding_article.number_of_steps = std::stoi(number_of_steps);

			std::cout << adding_article.name << std::endl;
			std::cout << number_of_steps << std::endl;

			std::string file_line;

		//adding article recources
			while (std::getline(file, file_line)) {
				adding_article.steps_and_pictures.push_back(steps);
				std::cout << file_line << std::endl;
				std::smatch match;
				std::regex reg_first("([^;]*)");
				std::regex_search(file_line, match, reg_first);
				file_line = match.suffix().str();
				std::regex reg("(;[^;]*)");
				while (!file_line.empty()) {
					std::regex_search(file_line, match, reg);
					std::string matched_path = match[0];
					matched_path.erase(matched_path.begin());
					std::cout << matched_path << std::endl;
					adding_article.steps_and_pictures[step_of_article].push_back(matched_path);
					file_line = match.suffix().str();
				}
				step_of_article++;
			}
		}
	}
	file.close();
}