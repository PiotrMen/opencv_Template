#pragma once
#ifndef IMAGE_FILTERS_H
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include "opencv2/opencv.hpp"
#include <SFML/Graphics.hpp>
#include "Universal_functions.h"
#include <SFML/System/Time.hpp>

class image_filters
{


public:
	void operator()(int thread_index);

};

#endif // IMAGE_FILTERS_H