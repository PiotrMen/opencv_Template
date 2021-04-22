#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "header.h"
#include "structures.h"


int main()
{
	sfml_objects objects;
	sArticles Article;
	objects.init_button_size(30);
	load_articles(Article);
	for (int i = 0; i < Article.steps_and_pictures.size(); i++) {
		for(int j = 0; j < Article.steps_and_pictures[i].size(); j++){
			std::cout << Article.steps_and_pictures[i][j] << " ";
		}
		std::cout << std::endl;
	}
	while (objects.getWindowIsOpen()) 
	{
		//Update
		objects.update();
		//Render
		objects.render();

	}

	return 0;
}
