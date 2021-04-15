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
	std::vector <std::vector <sf::Sprite>> sprites; //sprites in every step

};

#endif // !STRUCTURES_H