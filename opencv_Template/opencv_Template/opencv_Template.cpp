
#include <iostream>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>

using namespace cv;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Not Tetris");

	sf::Event event;

	while (window.isOpen()) {

		Mat test = imread("NBA.jpg", IMREAD_UNCHANGED);
		imshow("NBA_LOGO", test);

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}
	}

	return 0;
}
