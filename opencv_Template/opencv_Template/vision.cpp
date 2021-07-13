#include "vision.h"

void thread_vision::operator()(int index)
{
	cv::VideoCapture camera(index);
	camera.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
	cv::Mat image;
	while (true)
	{
		camera.read(image);
		imshow("main" + index, image);
		cv::waitKey(30);
	}
}