#include "articles.h"
#include <regex>

void load_articles(std::vector <sArticles> &articles)
{
	std::ifstream file;
	file.open("resources/articles.txt");
	int step_of_article = 0;

	// empty vectors used in loading steps in article
	std::vector<std::string> steps;
	std::vector<std::pair <int, int>> coordinates;
	std::vector<float> rotation;
	std::vector<float> scale;

	std::vector<std::string> texts;
	std::vector<std::pair<int, int>> text_coordinates;
	std::vector<float> text_rotation;
	std::vector<float> text_scale;

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

				article.pictures.push_back(steps);
				std::smatch match;
				std::regex reg("([a-zA-Z0-9 _\\\\:]*\\.[a-zA-Z0-9]*)");
				
				// loading paths in current step

				while (!file_line.empty()) {
					std::regex_search(file_line, match, reg);
					std::string matched_path = match[0];
					article.pictures[step_of_article].push_back(matched_path);
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

				//loading rotations in current step

				std::getline(file, file_line);
				article.rotation_of_pictures.push_back(rotation);
				std::smatch match_rotation;
				std::regex regex_rotation(";([0-9]*\\.[0-9])");

				while (!file_line.empty()) {
					std::regex_search(file_line, match_rotation, regex_rotation);
					float matched_rotation;
					matched_rotation = std::stof(match_rotation[1]);
					article.rotation_of_pictures[step_of_article].push_back(matched_rotation);
					file_line = match_rotation.suffix().str();
				}

				//loading scale in current step

				std::getline(file, file_line);
				article.scale_of_pictures.push_back(scale);
				std::smatch match_scale;
				std::regex regex_scale(";([0-9]*\\.[0-9])");

				while (!file_line.empty()) {
					std::regex_search(file_line, match_scale, regex_scale);
					float matched_scale;
					matched_scale = std::stof(match_scale[1]);
					article.scale_of_pictures[step_of_article].push_back(matched_scale);
					file_line = match_scale.suffix().str();
				}

				// loading texts in current step

				std::getline(file, file_line);

				article.displayed_text.push_back(texts);
				std::smatch match_text;
				std::regex regex_texts(";\"(.*)\"");

				while (!file_line.empty()) {
					std::regex_search(file_line, match_text, regex_texts);
					std::string matched_text = match_text[1];
					article.displayed_text[step_of_article].push_back(matched_text);
					file_line = match.suffix().str();
				}

				// loading text coordinates in current step

				std::getline(file, file_line);

				article.coordinates_of_texts.push_back(text_coordinates);
				std::smatch match_text_coordinates;
				std::regex regex_text_coordinates("\\(([0-9]*),([0-9]*)\\)");

				while (!file_line.empty()) {
					std::regex_search(file_line, match_text_coordinates, regex_text_coordinates);
					std::pair <int, int> matched_text_coordinates;
					matched_text_coordinates.first = std::stoi(match_text_coordinates[1]);
					matched_text_coordinates.second = std::stoi(match_text_coordinates[2]);
					article.coordinates_of_texts[step_of_article].push_back(matched_text_coordinates);
					file_line = match_text_coordinates.suffix().str();
				}
				
				//loading text rotations in current step

				std::getline(file, file_line);
				article.rotation_of_texts.push_back(text_rotation);
				std::smatch match_text_rotation;
				std::regex regex_text_rotation(";([0-9]*\\.[0-9])");

				while (!file_line.empty()) {
					std::regex_search(file_line, match_text_rotation, regex_text_rotation);
					float matched_text_rotation;
					matched_text_rotation = std::stof(match_text_rotation[1]);
					article.rotation_of_texts[step_of_article].push_back(matched_text_rotation);
					file_line = match_text_rotation.suffix().str();
				}

				//loading text scale in current step

				std::getline(file, file_line);
				article.scale_of_texts.push_back(text_scale);
				std::smatch match_text_scale;
				std::regex regex_text_scale(";([0-9]*\\.[0-9])");

				while (!file_line.empty()) {
					std::regex_search(file_line, match_text_scale, regex_text_scale);
					float matched_text_scale;
					matched_text_scale = std::stof(match_text_scale[1]);
					article.scale_of_texts[step_of_article].push_back(matched_text_scale);
					file_line = match_text_scale.suffix().str();
				}

				step_of_article++;
			}
			articles.push_back(article);
		}
	}
	file.close();
}
