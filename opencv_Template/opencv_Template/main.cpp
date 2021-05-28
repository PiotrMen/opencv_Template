#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "window_functions_.h"
#include "menu_functions.h"
#include "articles.h"



int main()
{
	sfml_objects objects;
	menu_sfml_objects menu_objects;
	std::vector <sArticles> Articles;
	objects.init_button_size(30);
	menu_objects.init_button_size(30, 120);
	load_articles(Articles);
	int current_step = 0;	// step of current article
	int current_window = 0;

	// wyświetlanie pomocnicze (do usunięcia)

	for (int k = 0; k < Articles.size(); k++)
	{
		std::cout << Articles[k].name << std::endl;
		std::cout << Articles[k].number_of_steps << std::endl;
		for (int i = 0; i < Articles[k].pictures.size(); i++) {
			for (int j = 0; j < Articles[k].pictures[i].size(); j++) {
				std::cout << Articles[k].pictures[i][j] << " ";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].coordinates_of_pictures[i].size(); z++) {
				std::cout << "(" << Articles[k].coordinates_of_pictures[i][z].first << "," << Articles[k].coordinates_of_pictures[i][z].second << ")";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].rotation_of_pictures[i].size(); z++) {
				std::cout << Articles[k].rotation_of_pictures[i][z] << " ";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].scale_of_pictures[i].size(); z++) {
				std::cout << Articles[k].scale_of_pictures[i][z] << " ";
			}
			std::cout << std::endl;

			for (int j = 0; j < Articles[k].displayed_text[i].size(); j++) {
				std::cout << Articles[k].displayed_text[i][j] << " ";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].coordinates_of_texts[i].size(); z++) {
				std::cout << "(" << Articles[k].coordinates_of_texts[i][z].first << "," << Articles[k].coordinates_of_texts[i][z].second << ")";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].rotation_of_texts[i].size(); z++) {
				std::cout << Articles[k].rotation_of_texts[i][z] << " ";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].scale_of_texts[i].size(); z++) {
				std::cout << Articles[k].scale_of_texts[i][z] << " ";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].size_of_rectangle[i].size(); z++) {
				std::cout << Articles[k].size_of_rectangle[i][z].first << "," << Articles[k].size_of_rectangle[i][z].second;
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].coordinates_of_rectangles[i].size(); z++) {
				std::cout << "(" << Articles[k].coordinates_of_rectangles[i][z].first << "," << Articles[k].coordinates_of_rectangles[i][z].second << ")";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].rotation_of_rectangles[i].size(); z++) {
				std::cout << Articles[k].rotation_of_rectangles[i][z] << " ";
			}
			std::cout << std::endl;

		}
		std::cout << std::endl;
	}

	//

	while (objects.getWindowIsOpen() && menu_objects.getWindowIsOpen()) 
	{
		//Menu update
		menu_objects.update(current_step, current_window);
		//Update
		objects.update(current_step, current_window);


		menu_objects.render(Articles, current_step, current_window);
		//Render
		objects.render(Articles, current_step, current_window);
	}

	return 0;
}
