#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "window_functions_.h"
#include "menu_functions.h"
#include "csv_read.h"
#include "Universal_functions.h"

// Data vectors
std::vector <sData> articles_in_boxes;
std::vector <sData> left_articles;


int main()
{
	sfml_objects objects;
	menu_sfml_objects menu_objects;
	//coordinates of buttons
	menu_objects.init_buttons_coords();
	//size of buttons
	objects.init_button_size(30);
	menu_objects.init_button_size(30,120);

	load_csv(articles_in_boxes, left_articles);
	save_csv(articles_in_boxes, left_articles);


	int current_step = 0;	// step of current article
	int current_window = 0;

	// wyświetlanie pomocnicze (do usunięcia)

	while (objects.getWindowIsOpen() && menu_objects.getWindowIsOpen()) 
	{
		//Menu update
		menu_objects.update(current_step, current_window);
		//Update
		objects.update(current_step, current_window);


		menu_objects.render(current_step, current_window);
		//Render
		objects.render(current_step, current_window);
	}

	return 0;
}
