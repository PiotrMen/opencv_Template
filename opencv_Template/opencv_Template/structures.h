#pragma once
#ifndef STRUCTURES_H
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
	std::vector<std::vector<std::string>> steps_and_pictures; //picture paths in every step
	std::vector<std::vector<int, int>> coordinates_of_pictures; // contains coordinates of every loaded picture
	std::vector<std::vector<float>> rotation_of_pictures; // contains rotation value of every loaded picture
	std::vector<std::vector<float>> scale_of_pictures; // contains scale value of every loaded picture

	std::vector <std::vector <sf::Sprite>> sprites; //sprites in every step
};

void load_articles(std::vector <sArticles> &articles);

#endif // !STRUCTURES_H