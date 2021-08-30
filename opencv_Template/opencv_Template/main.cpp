#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include "window_functions_.h"
#include "menu_functions.h"
#include "csv_read.h"
#include "Universal_functions.h"
#include "vision.h"
#include "live_chart.h"


std::mutex m;
std::mutex m2;

// Sequence vector
std::vector <sData> sequence;

// Global data
sGlobal_data data_box;


int main()
{
	ShowWindow(GetConsoleWindow(), SW_NORMAL);
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	sfml_objects objects;
	menu_sfml_objects menu_objects;
	cLive_chart live_chart(400, 796, 200);

	//coordinates of buttons
	menu_objects.init_buttons_coords();
	//size of buttons
	objects.init_button_size(100);
	menu_objects.init_button_size(100, 120);

	// Loading database
	std::vector <sData> database;
	load_csv_database(database);

	int current_window = 0;


	std::thread th(thread_vision(), 1);
	
	//sf::Clock zegar;
	//sf::Time czas;
	
	while (objects.getWindowIsOpen() && menu_objects.getWindowIsOpen())
	{
		//zegar.restart();

		//Menu update
		menu_objects.update(data_box.current_step, current_window);

		//Update
		objects.update(data_box.current_step, database);

		objects.sequence_activated = menu_objects.start_sequention;

		menu_objects.render(data_box.current_step, live_chart.if_active);

		//Render
		objects.render(data_box.current_step, menu_objects.current_menu_window, menu_objects.vector_rectangles, database, menu_objects.which_box_is_writing);
		
		/*live_chart.update(menu_objects.current_menu_window, menu_objects.if_clear, menu_objects.if_display, menu_objects.menu_window);
		live_chart.render(menu_objects.if_clear, menu_objects.if_display, menu_objects.menu_window);*/

		//czas = zegar.getElapsedTime();
		//std::cout << czas.asMilliseconds() << std::endl;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			data_box.global_exit = true;

		//std::cout << data_box.red_button << "   " << data_box.green_button << std::endl;
		if (data_box.global_exit) 
			break;
	}
	th.join();
	return 0;
}
