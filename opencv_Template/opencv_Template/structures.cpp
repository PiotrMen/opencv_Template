#include "structures.h"
#include <regex>

void load_articles(std::vector <sArticles> &articles)
{
	std::ifstream file;
	file.open("resources/articles.txt");
	int step_of_article = 0;

	// empty vector used in loading steps in article
	std::vector<std::string> steps;
	std::vector<std::pair <int, int>> coordinates;


	if (file.is_open())
	{
		std::string article_name;
		
		// loading new article

		while (std::getline(file, article_name))
		{
			//adding article name

			sArticles article;
			article.name = article_name;

			step_of_article = 0;

			//adding article number of steps

			std::string number_of_steps;
			std::getline(file, number_of_steps);
			article.number_of_steps = std::stoi(number_of_steps);

			std::string file_line;
			
			//adding article resources

			// loading steps in current article

			while (true) {
				std::getline(file, file_line);
				if (file_line.empty())
				{
					break;
				}

				article.steps_and_pictures.push_back(steps);
				std::smatch match;
				std::regex reg("([a-zA-Z0-9 _\\\\:]*\\.[a-zA-Z0-9]*)");
				
				// loading paths in current step

				while (!file_line.empty()) {
					std::regex_search(file_line, match, reg);
					std::string matched_path = match[0];
					article.steps_and_pictures[step_of_article].push_back(matched_path);
					file_line = match.suffix().str();
				}

				// loading coordinates in current step

				std::getline(file, file_line);

				article.coordinates_of_pictures.push_back(coordinates);
				std::smatch match_coordinates;
				std::regex regex_coordinates("\\(([0-9]*),([0-9]*)\\)");

				while (!file_line.empty()) {
					std::regex_search(file_line, match_coordinates, regex_coordinates);
					std::pair <int, int> matched_coordinates;
					matched_coordinates.first = std::stoi(match_coordinates[1]);
					matched_coordinates.second = std::stoi(match_coordinates[2]);
					article.coordinates_of_pictures[step_of_article].push_back(matched_coordinates);
					file_line = match_coordinates.suffix().str();
				}

				//jeszcze tutaj while z rotacja i skala

				step_of_article++;
			}
			articles.push_back(article);
		}
	}
	file.close();
}