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

	std::vector<std::vector<std::string>> displayed_text; //text (or multiple texts) displayed alongside pictures
	std::vector<std::vector<std::pair<int, int>>> coordinates_of_texts; //contains coordinates of every text
	std::vector<std::vector<float>> rotation_of_texts; // (float) rotation of every text
	std::vector<std::vector<float>> scale_of_texts; //scale of every text

	std::vector<std::vector<std::pair<int, int>>> size_of_rectangle; // contains size of rectangles
	std::vector<std::vector<std::pair<int, int>>> coordinates_of_rectangles; // contains coordinates of rectangles
	std::vector<std::vector<float>> rotation_of_rectangles; // contains rotation of rectangles

};

void load_articles(std::vector <sArticles> &articles);


#endif // !ARTICLES_H