#include "articles.h"

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

	std::vector<std::pair<int, int>> rectangle_size;
	std::vector<std::pair<int, int>> rectangle_coordinates;
	std::vector<float> rectangle_rotation;

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

				//article.pictures.push_back(steps);
				std::smatch match;
				std::regex reg("([a-zA-Z0-9 _\\\\:]*\\.[a-zA-Z0-9]*)");

				// loading paths in current step

				article.pictures.push_back(steps);

				while (!file_line.empty()) {
					std::regex_search(file_line, match, reg);
					if (match[0] != "")
					{
						std::string matched_path = match[0];
						article.pictures[step_of_article].push_back(matched_path);
					}
					file_line = match.suffix().str();
				}

				// loading coordinates in current step

				std::getline(file, file_line);

				//article.coordinates_of_pictures.push_back(coordinates);
				std::smatch match_coordinates;
				std::regex regex_coordinates("\\(([0-9]*),([0-9]*)\\)");

				article.coordinates_of_pictures.push_back(coordinates);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_coordinates, regex_coordinates);
					if (match_coordinates[0] != "")
					{
						std::pair <int, int> matched_coordinates;
						matched_coordinates.first = std::stoi(match_coordinates[1]);
						matched_coordinates.second = std::stoi(match_coordinates[2]);
						article.coordinates_of_pictures[step_of_article].push_back(matched_coordinates);
					}
					file_line = match_coordinates.suffix().str();
				}

				//loading rotations in current step

				std::getline(file, file_line);
				//article.rotation_of_pictures.push_back(rotation);
				std::smatch match_rotation;
				std::regex regex_rotation(";([0-9]*\\.[0-9])");

				article.rotation_of_pictures.push_back(rotation);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_rotation, regex_rotation);
					if (match_rotation[0] != "")
					{
						float matched_rotation;
						matched_rotation = std::stof(match_rotation[1]);
						article.rotation_of_pictures[step_of_article].push_back(matched_rotation);
					}
					file_line = match_rotation.suffix().str();
				}

				//loading scale in current step

				std::getline(file, file_line);
				//article.scale_of_pictures.push_back(scale);
				std::smatch match_scale;
				std::regex regex_scale(";([0-9]*\\.[0-9])");

				article.scale_of_pictures.push_back(scale);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_scale, regex_scale);
					if (match_scale[0] != "")
					{
						float matched_scale;
						matched_scale = std::stof(match_scale[1]);
						article.scale_of_pictures[step_of_article].push_back(matched_scale);
					}
					file_line = match_scale.suffix().str();
				}

				// loading texts in current step

				std::getline(file, file_line);

				//article.displayed_text.push_back(texts);
				std::smatch match_text;
				std::regex regex_texts(";\"(.*)\"");

				article.displayed_text.push_back(texts);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_text, regex_texts);
					if (match_text[0] != "")
					{
						std::string matched_text = match_text[1];
						article.displayed_text[step_of_article].push_back(matched_text);
					}
					file_line = match.suffix().str();
				}

				// loading text coordinates in current step

				std::getline(file, file_line);

				//article.coordinates_of_texts.push_back(text_coordinates);
				std::smatch match_text_coordinates;
				std::regex regex_text_coordinates("\\(([0-9]*),([0-9]*)\\)");

				article.coordinates_of_texts.push_back(text_coordinates);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_text_coordinates, regex_text_coordinates);
					if (match_text_coordinates[0] != "")
					{
						std::pair <int, int> matched_text_coordinates;
						matched_text_coordinates.first = std::stoi(match_text_coordinates[1]);
						matched_text_coordinates.second = std::stoi(match_text_coordinates[2]);
						article.coordinates_of_texts[step_of_article].push_back(matched_text_coordinates);
					}
					file_line = match_text_coordinates.suffix().str();
				}

				//loading text rotations in current step

				std::getline(file, file_line);
				//article.rotation_of_texts.push_back(text_rotation);
				std::smatch match_text_rotation;
				std::regex regex_text_rotation(";([0-9]*\\.[0-9])");

				article.rotation_of_texts.push_back(text_rotation);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_text_rotation, regex_text_rotation);
					if (match_text_rotation[0] != "")
					{
						float matched_text_rotation;
						matched_text_rotation = std::stof(match_text_rotation[1]);
						article.rotation_of_texts[step_of_article].push_back(matched_text_rotation);
					}
					file_line = match_text_rotation.suffix().str();
				}

				//loading text scale in current step

				std::getline(file, file_line);
				//article.scale_of_texts.push_back(text_scale);
				std::smatch match_text_scale;
				std::regex regex_text_scale(";([0-9]*\\.[0-9])");

				article.scale_of_texts.push_back(text_scale);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_text_scale, regex_text_scale);
					if (match_text_scale[0] != "")
					{
						float matched_text_scale;
						matched_text_scale = std::stof(match_text_scale[1]);
						article.scale_of_texts[step_of_article].push_back(matched_text_scale);
					}
					file_line = match_text_scale.suffix().str();
				}

				// loading rectangle size in current step

				std::getline(file, file_line);

				//article.size_of_rectangle.push_back(rectangle_size);
				std::smatch match_rectangle_size;
				std::regex regex_rectangle_size("([0-9]*),([0-9]*)");

				article.size_of_rectangle.push_back(rectangle_size);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_rectangle_size, regex_rectangle_size);
					if (match_rectangle_size[0] != "")
					{
						std::pair <int, int> matched_rectangle_size;
						matched_rectangle_size.first = std::stoi(match_rectangle_size[1]);
						matched_rectangle_size.second = std::stoi(match_rectangle_size[2]);
						article.size_of_rectangle[step_of_article].push_back(matched_rectangle_size);
					}
					file_line = match_rectangle_size.suffix().str();
				}

				// loading rectangle coordinates in current step

				std::getline(file, file_line);

				//article.coordinates_of_rectangles.push_back(rectangle_coordinates);
				std::smatch match_rectangle_coordinates;
				std::regex regex_rectangle_coordinates("\\(([0-9]*),([0-9]*)\\)");

				article.coordinates_of_rectangles.push_back(rectangle_coordinates);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_rectangle_coordinates, regex_rectangle_coordinates);
					if (match_rectangle_coordinates[0] != "")
					{
						std::pair <int, int> matched_rectangle_coordinates;
						matched_rectangle_coordinates.first = std::stoi(match_rectangle_coordinates[1]);
						matched_rectangle_coordinates.second = std::stoi(match_rectangle_coordinates[2]);
						article.coordinates_of_rectangles[step_of_article].push_back(matched_rectangle_coordinates);
					}
					file_line = match_rectangle_coordinates.suffix().str();
				}

				//loading rectangle rotations in current step

				std::getline(file, file_line);
				//article.rotation_of_rectangles.push_back(rectangle_rotation);
				std::smatch match_rectangle_rotation;
				std::regex regex_rectangle_rotation(";([0-9]*\\.[0-9])");

				article.rotation_of_rectangles.push_back(rectangle_rotation);

				while (!file_line.empty()) {
					std::regex_search(file_line, match_rectangle_rotation, regex_rectangle_rotation);
					if (match_rectangle_rotation[0] != "")
					{
						float matched_rectangle_rotation;
						matched_rectangle_rotation = std::stof(match_rectangle_rotation[1]);
						article.rotation_of_rectangles[step_of_article].push_back(matched_rectangle_rotation);
					}
					file_line = match_rectangle_rotation.suffix().str();
				}

				step_of_article++;
			}
			articles.push_back(article);
		}
	}
	file.close();
}
void save_articles(std::vector <sArticles> &articles)
{
	std::ofstream file;
	file.open("resources/articles.txt");
	if (file.is_open())
	{
		for (int i = 0; i < articles.size(); i++)
		{
			// Writing name of article

			file << articles[i].name << std::endl;

			// Writing number of steps in article

			file << articles[i].number_of_steps << std::endl;

			// Writing paths and data in article

			for (int k = 1; k <= articles[i].number_of_steps; k++)
			{
				// Writing paths to pictures in current step

				file << k;

				for (int l = 0; l < articles[i].pictures[k - 1].size(); l++)
				{
					file << ";" << articles[i].pictures[k - 1][l];
				}

				file << std::endl;

				// Writing picture coordiantes in current step

				file << k;

				for (int l = 0; l < articles[i].coordinates_of_pictures[k - 1].size(); l++)
				{
					file << ";(" << articles[i].coordinates_of_pictures[k - 1][l].first << "," << articles[i].coordinates_of_pictures[k - 1][l].second << ")";
				}

				file << std::endl;

				// Writing picture rotation in current step

				file << k;

				for (int l = 0; l < articles[i].rotation_of_pictures[k - 1].size(); l++)
				{

					file << ";" << std::fixed << std::setprecision(1) << articles[i].rotation_of_pictures[k - 1][l];
				}
				file << std::endl;

				// Writing picture scale in current step

				file << k;

				for (int l = 0; l < articles[i].scale_of_pictures[k - 1].size(); l++)
				{

					file << ";" << articles[i].scale_of_pictures[k - 1][l];
				}
				file << std::endl;

				// Writing text in current step

				file << k;

				for (int l = 0; l < articles[i].displayed_text[k - 1].size(); l++)
				{

					file << ";" << "\"" << articles[i].displayed_text[k - 1][l] << "\"";
				}
				file << std::endl;

				// Writing text coordiantes in current step

				file << k;

				for (int l = 0; l < articles[i].coordinates_of_texts[k - 1].size(); l++)
				{
					file << ";(" << articles[i].coordinates_of_texts[k - 1][l].first << "," << articles[i].coordinates_of_texts[k - 1][l].second << ")";
				}

				file << std::endl;

				// Writing text rotation in current step

				file << k;

				for (int l = 0; l < articles[i].rotation_of_texts[k - 1].size(); l++)
				{

					file << ";" << std::fixed << std::setprecision(1) << articles[i].rotation_of_texts[k - 1][l];
				}
				file << std::endl;

				// Writing text scale in current step

				file << k;

				for (int l = 0; l < articles[i].scale_of_texts[k - 1].size(); l++)
				{

					file << ";" << articles[i].scale_of_texts[k - 1][l];
				}
				file << std::endl;

				// Writing rectangle size in current step

				file << k;

				for (int l = 0; l < articles[i].size_of_rectangle[k - 1].size(); l++)
				{
					file << ";" << articles[i].size_of_rectangle[k - 1][l].first << "," << articles[i].size_of_rectangle[k - 1][l].second;
				}

				file << std::endl;

				// Writing rectangle coordiantes in current step

				file << k;

				for (int l = 0; l < articles[i].coordinates_of_rectangles[k - 1].size(); l++)
				{
					file << ";(" << articles[i].coordinates_of_rectangles[k - 1][l].first << "," << articles[i].coordinates_of_rectangles[k - 1][l].second << ")";
				}

				file << std::endl;

				// Writing rectangle rotation in current step

				file << k;

				for (int l = 0; l < articles[i].rotation_of_rectangles[k - 1].size(); l++)
				{

					file << ";" << std::fixed << std::setprecision(1) << articles[i].rotation_of_rectangles[k - 1][l];
				}
				file << std::endl;

			}
			file << std::endl;
		}
	}
	file.close();
}
void delete_article(std::vector <sArticles> &articles, int id_of_article)
{
	// Checking if there is articles with given id

	if (id_of_article >= 0 && id_of_article < articles.size())
	{
		articles.erase(articles.begin() + id_of_article);
	}

}
void delete_step_in_article(std::vector <sArticles> &articles, int id_of_article, int step_of_article)
{
	// Checking if there is articles with given id

	if (id_of_article >= 0 && id_of_article < articles.size())
	{
		if (step_of_article >= 0 && step_of_article < articles[id_of_article].number_of_steps)
		{
			articles[id_of_article].number_of_steps = articles[id_of_article].number_of_steps - 1;

			articles[id_of_article].pictures.erase(articles[id_of_article].pictures.begin() + step_of_article);
			articles[id_of_article].coordinates_of_pictures.erase(articles[id_of_article].coordinates_of_pictures.begin() + step_of_article);
			articles[id_of_article].rotation_of_pictures.erase(articles[id_of_article].rotation_of_pictures.begin() + step_of_article);
			articles[id_of_article].scale_of_pictures.erase(articles[id_of_article].scale_of_pictures.begin() + step_of_article);

			articles[id_of_article].displayed_text.erase(articles[id_of_article].displayed_text.begin() + step_of_article);
			articles[id_of_article].coordinates_of_texts.erase(articles[id_of_article].coordinates_of_texts.begin() + step_of_article);
			articles[id_of_article].rotation_of_texts.erase(articles[id_of_article].rotation_of_texts.begin() + step_of_article);
			articles[id_of_article].scale_of_texts.erase(articles[id_of_article].scale_of_texts.begin() + step_of_article);

			articles[id_of_article].size_of_rectangle.erase(articles[id_of_article].size_of_rectangle.begin() + step_of_article);
			articles[id_of_article].coordinates_of_rectangles.erase(articles[id_of_article].coordinates_of_rectangles.begin() + step_of_article);
			articles[id_of_article].rotation_of_rectangles.erase(articles[id_of_article].rotation_of_rectangles.begin() + step_of_article);
		}
	}
}

void delete_element_in_article(std::vector <sArticles> &articles, int id_of_article, int step_of_article, char type_of_element, int id_of_element)
{
	// Checking if there is articles with given id

	if (id_of_article >= 0 && id_of_article < articles.size())
	{
		if (step_of_article >= 0 && step_of_article < articles[id_of_article].number_of_steps)
		{
			if (type_of_element == 'p')
			{
				if (id_of_element >= 0 && id_of_element < articles[id_of_article].pictures.size())
				{
					if (articles[id_of_article].pictures[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].pictures[step_of_article].erase(articles[id_of_article].pictures[step_of_article].begin() + id_of_element);
					}
					if (articles[id_of_article].coordinates_of_pictures[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].coordinates_of_pictures[step_of_article].erase(articles[id_of_article].coordinates_of_pictures[step_of_article].begin() + id_of_element);
					}
					if (articles[id_of_article].rotation_of_pictures[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].rotation_of_pictures[step_of_article].erase(articles[id_of_article].rotation_of_pictures[step_of_article].begin() + id_of_element);
					}
					if (articles[id_of_article].scale_of_pictures[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].scale_of_pictures[step_of_article].erase(articles[id_of_article].scale_of_pictures[step_of_article].begin() + id_of_element);
					}
				}
			}
			if (type_of_element == 't')
			{
				if (id_of_element >= 0 && id_of_element < articles[id_of_article].displayed_text.size())
				{
					if (articles[id_of_article].displayed_text[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].displayed_text[step_of_article].erase(articles[id_of_article].displayed_text[step_of_article].begin() + id_of_element);
					}
					if (articles[id_of_article].coordinates_of_texts[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].coordinates_of_texts[step_of_article].erase(articles[id_of_article].coordinates_of_texts[step_of_article].begin() + id_of_element);
					}
					if (articles[id_of_article].rotation_of_texts[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].rotation_of_texts[step_of_article].erase(articles[id_of_article].rotation_of_texts[step_of_article].begin() + id_of_element);
					}
					if (articles[id_of_article].scale_of_texts[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].scale_of_texts[step_of_article].erase(articles[id_of_article].scale_of_texts[step_of_article].begin() + id_of_element);
					}
				}
			}
			if (type_of_element == 'r')
			{
				if (id_of_element >= 0 && id_of_element < articles[id_of_article].size_of_rectangle.size())
				{
					if (articles[id_of_article].size_of_rectangle[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].size_of_rectangle[step_of_article].erase(articles[id_of_article].size_of_rectangle[step_of_article].begin() + id_of_element);
					}
					if (articles[id_of_article].coordinates_of_rectangles[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].coordinates_of_rectangles[step_of_article].erase(articles[id_of_article].coordinates_of_rectangles[step_of_article].begin() + id_of_element);
					}
					if (articles[id_of_article].rotation_of_rectangles[step_of_article].size() > id_of_element)
					{
						articles[id_of_article].rotation_of_rectangles[step_of_article].erase(articles[id_of_article].rotation_of_rectangles[step_of_article].begin() + id_of_element);
					}
				}
			}
			// do poprawienia usuwanie kroku w przypadku pustych trzech wektorow

			if (articles[id_of_article].pictures[step_of_article].size() == 0 && articles[id_of_article].displayed_text[step_of_article].size() == 0 && articles[id_of_article].size_of_rectangle[step_of_article].size() == 0)
			{
				delete_step_in_article(articles, id_of_article, step_of_article);
			}
		}
	}
}
