#include "structures.h"
#include <regex>

void load_articles(std::vector <sArticles> &articles)
{
	std::ifstream file;
	file.open("resources/articles.txt");
	int step_of_article = 0;
	std::vector<std::string> steps;
	sArticles article;

	if (file.is_open())
	{
		std::string article_name;
		//adding article name

		//for(int i = 0; std::getline(file, article_name); i++)
		while (std::getline(file, article.name))
		{
			step_of_article = 0;

		//adding article number of steps
			std::string number_of_steps;
			std::getline(file, number_of_steps);
			article.number_of_steps = std::stoi(number_of_steps);

			std::string file_line;
			
		//adding article recources
			while (std::getline(file, file_line)) {
				
				article.steps_and_pictures.push_back(steps);
				std::smatch match;
				std::regex reg("(;[^;]*)");
				std::regex_search(file_line, match, reg);
				file_line = match.suffix().str();
				//std::regex reg("(;[^;:]*)");
				while (!file_line.empty()) {
					//std::regex_search(file_line, match, reg);
					std::string matched_path = match[0];
					//matched_path.erase(matched_path.begin());
					article.steps_and_pictures[step_of_article].push_back(matched_path);
					file_line = match.suffix().str();
				}
				step_of_article++;
			}
		}
	}
	file.close();
}