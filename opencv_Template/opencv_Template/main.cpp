﻿#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include "window_functions_.h"
#include "menu_functions.h"
#include "csv_read.h"
#include "Universal_functions.h"
#include "vision.h"

std::mutex m;

// Sequence vector
std::vector <sData> sequence;

// Global data
sGlobal_data data_box;


int main()
{
	menu_sfml_objects menu_objects;
	sfml_objects objects;

	//coordinates of buttons
	menu_objects.init_buttons_coords();
	//size of buttons
	objects.init_button_size(100);
	menu_objects.init_button_size(100,120);


	//int current_step = 0;	// step of current article
	int current_window = 0;


	std::thread th(thread_vision(), 1);

	while (objects.getWindowIsOpen() && menu_objects.getWindowIsOpen())
	{
		//Menu update
		menu_objects.update(data_box.current_step, current_window);

		//Update
		objects.update(data_box.current_step, current_window);

		objects.sequence_activated = menu_objects.start_sequention;

		menu_objects.render(data_box.current_step, current_window);
		//Render
		objects.render(data_box.current_step, current_window);
		
		//m.lock();

		//std::cout << data_box.red_button << "   " << data_box.green_button << std::endl;
		if (data_box.global_exit) {
			break;
		}

		//m.unlock();
	}
	th.join();
	return 0;
}
