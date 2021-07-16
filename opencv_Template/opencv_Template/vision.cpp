#include "vision.h"

bool thread_vision::Is_button_covered(int select_button) {
	cv::Mat cropped_image;
	cv::Mat Kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	if (select_button == 0) {
		cv::Rect crop_region(50, 700, 380, 380);
		cropped_image = image(crop_region);
	}
	else if (select_button == 1){
		cv::Rect crop_region(1505, 705, 350, 350);
		cropped_image = image(crop_region);
		cv::cvtColor(cropped_image, cropped_image, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(cropped_image, cropped_image, cv::Size(3, 3), 3, 0);
		cv::Canny(cropped_image, cropped_image, 150, 200);
		cv::dilate(cropped_image, cropped_image, Kernel);
	}

	imshow("Przycisk"+ std::to_string(select_button), cropped_image);

	if (check_pattern(cropped_image, cv::Point(1505, 705), 500, 700))
		return true;
	else
		return false;

}

bool thread_vision::check_pattern(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(input_image, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	cv::Rect boundRect(dxdy, input_image.size());
	
	cv::Vec2i areas = (0, 0);
	int counter = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		float peri = cv::arcLength(contours[i], true);
		cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
		
		if ((int)conPoly[i].size() == 4 && contourArea(contours[i]) > 3000)
		{
			areas[counter] = contourArea(contours[i]);
			counter++;
		}

		//if((int)conPoly[i].size() == 4)
		//	cv::drawContours(image, conPoly, i, cv::Scalar(0, 255, 0), 1, cv::LINE_8, -1, 0, dxdy);
	}

	std::cout << std::abs(areas[0] - areas[1]) << std::endl;

	if (std::abs(areas[0] - areas[1]) > lower_value && std::abs(areas[0] - areas[1]) < upper_value)
	{
		cv::rectangle(image, boundRect, cv::Scalar(0, 255, 0), 5);

		//imshow("Przycisk2", image);
		return true;
	}
	else
	{
		cv::rectangle(image, boundRect, cv::Scalar(0, 0, 255), 5);
		//imshow("Przycisk2", image);
		return false;
	}
}


void thread_vision::display_Tracksbars(int &hmin, int &hmax, int &smin, int &smax, int &vmin, int &vmax) {
	cv::Mat imageHSV;
	cv::Mat mask;
	cv::cvtColor(this->trackbars_img, imageHSV, cv::COLOR_BGR2GRAY);

	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179); // dla lewego przycisku 90 // dla prawego 52
	cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
	cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

	cv::Scalar lower(hmin, smin, vmin);
	cv::Scalar upper(hmax, smax, vmax);
	cv::inRange(imageHSV, lower, upper, mask);

	imshow("mask1", imageHSV);
	imshow("mask", mask);
}

void thread_vision::operator()(int index)
{
	cv::VideoCapture camera(index);
	camera.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
	int hmin = 0, hmax=179, smin=0, smax=255, vmin=0, vmax=255;



	while (true)
	{
		//camera trigger
		camera.read(image);
		cv::rotate(image,image,cv::ROTATE_180);

		//thread_vision::Is_button_covered(0);
		thread_vision::Is_button_covered(1);
		//thread_vision::display_Tracksbars(hmin, hmax, smin, smax, vmin, vmax);

		//showing image
		imshow("main", image);

		cv::waitKey(30);
	}
}


