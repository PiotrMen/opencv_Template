#pragma once
#ifndef VISION_H
#include <thread>
#include <iostream>
#include "opencv2/opencv.hpp"

class thread_vision
{

public:
	void operator()(int index);

private:

};



#endif // !VISION_H