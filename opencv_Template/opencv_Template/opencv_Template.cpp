#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "header.h"

//using namespace cv;

int main()
{
	sfml_objects objects;
	objects.init_button_size(30);

	while (objects.getWindowIsOpen()) 
	{
		//Update
		objects.update();
		//Render
		objects.render();

	}

	return 0;
}
