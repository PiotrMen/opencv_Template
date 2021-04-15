#include "structures.h"

void load_articles()
{
	sArticles adding_article;
	std::ifstream file;
	file.open("resources/articles.txt");

	if (file.is_open())
	{
		std::getline(file, adding_article.name);
		std::string number_of_steps;
		std::getline(file, number_of_steps);
		adding_article.number_of_steps = std::stoi(number_of_steps);
	}
	file.close();
}