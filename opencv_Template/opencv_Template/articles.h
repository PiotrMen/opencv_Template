#pragma once
#ifndef ARTICLES_H
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <regex>
#include <fstream>


struct sArticles
{
	int number_of_steps;
	std::string name;
	std::vector<std::vector<std::string>> pictures; //picture paths in every step
	std::vector<std::vector<std::pair<int, int>>> coordinates_of_pictures; // contains coordinates of every loaded picture
	std::vector<std::vector<float>> rotation_of_pictures; // contains rotation value of every loaded picture
	std::vector<std::vector<float>> scale_of_pictures; // contains scale value of every loaded picture
};

void load_articles(std::vector <sArticles> &articles);

#endif // !ARTICLES_H