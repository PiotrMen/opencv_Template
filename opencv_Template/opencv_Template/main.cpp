#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "window_functions_.h"
#include "articles.h"



int main()
{
	sfml_objects objects;
	std::vector <sArticles> Articles;
	objects.init_button_size(30);
	load_articles(Articles);
	int current_step = 0;

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
				std::cout << Articles[k].rotation_of_pictures[i][z]<< " ";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].scale_of_pictures[i].size(); z++) {
				std::cout << Articles[k].scale_of_pictures[i][z] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	
	//

	while (objects.getWindowIsOpen()) 
	{
		while (current_step <= Articles[0].number_of_steps) 
		{
			for (int i = 0; i < Articles[0].pictures.size(); i++) {
				objects.display_texture(Articles[0].coordinates_of_pictures[current_step][i].first, Articles[0].coordinates_of_pictures[current_step][i].second, Articles[0].pictures[current_step][i], Articles[0].scale_of_pictures[current_step][i], Articles[0].rotation_of_pictures[current_step][i]);
				objects.window->display();
			}

			objects.left_mouse_button_pressed(current_step);
		}
		//Update
		objects.update();
		//Render
		objects.render();
	}

	return 0;
}
