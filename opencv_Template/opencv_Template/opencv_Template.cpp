#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "header.h"
#include "structures.h"


int main()
{
	sfml_objects objects;
	std::vector <sArticles> Articles;
	objects.init_button_size(30);
	load_articles(Articles);

	// wyświetlanie pomocnicze (do usunięcia)
	
	for (int k = 0; k < Articles.size(); k++)
	{
		std::cout << Articles[k].name << std::endl;
		std::cout << Articles[k].number_of_steps << std::endl;
		for (int i = 0; i < Articles[k].steps_and_pictures.size(); i++) {
			for (int j = 0; j < Articles[k].steps_and_pictures[i].size(); j++) {
				std::cout << Articles[k].steps_and_pictures[i][j] << " ";
			}
			std::cout << std::endl;
			for (int z = 0; z < Articles[k].coordinates_of_pictures.size(); z++) {
				std::cout << "(" << Articles[k].coordinates_of_pictures[i][z].first << "," << Articles[k].coordinates_of_pictures[i][z].second << ")";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	
	//

	while (objects.getWindowIsOpen()) 
	{
		//Update
		objects.update();
		//Render
		objects.render();

	}

	return 0;
}
