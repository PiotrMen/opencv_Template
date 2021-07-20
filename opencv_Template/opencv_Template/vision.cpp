#include "vision.h"

cv::Mat thread_vision::button_filters(int select_button) 
{
	cv::Mat cropped_image;

	//	0 - Exit button
	//  1 - Confirmation button

	cv::Mat Kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	if (select_button == 0) {

		// Cropping image
		cv::Rect crop_region(50, 700, 380, 380);
		cropped_image = image(crop_region);

		// Filters
		cv::cvtColor(cropped_image, cropped_image, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(cropped_image, cropped_image, cv::Size(3, 3), 3, 0);
		cv::Canny(cropped_image, cropped_image, 84, 255);
		cv::dilate(cropped_image, cropped_image, Kernel);

		//Pomocnicze trackbary
		//cv::namedWindow("Trackbars", (640, 200));
		//cv::createTrackbar("Tresh Min", "Trackbars", &tresh_min, 255);
		//cv::createTrackbar("Tresh Max", "Trackbars", &tresh_max, 255);

		//Wyswietlanie pomocnicze
		//imshow("Przycisk" + std::to_string(select_button), cropped_image);

		return cropped_image;
	}
	else if (select_button == 1){

		// Cropping image
		cv::Rect crop_region(1505, 705, 350, 350);
		cropped_image = image(crop_region);

		// Filters
		cv::cvtColor(cropped_image, cropped_image, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(cropped_image, cropped_image, cv::Size(3, 3), 3, 0);
		cv::Canny(cropped_image, cropped_image, 84, 255);
		cv::dilate(cropped_image, cropped_image, Kernel);

		//Pomocnicze trackbary
		//cv::namedWindow("Trackbars", (640, 200));
		//cv::createTrackbar("Tresh Min", "Trackbars", &tresh_min, 255);
		//cv::createTrackbar("Tresh Max", "Trackbars", &tresh_max, 255);

		//Wyswietlanie pomocnicze
		//imshow("Przycisk" + std::to_string(select_button), cropped_image);

		return cropped_image;
	}
}

cv::Mat thread_vision::box_filters()
{
	cv::Mat cropped_image;

	m.lock();
	cropped_image = image(boxes[sequence[data_box.current_step].matched_rectangle]);
	TL_of_window = boxes[sequence[data_box.current_step].matched_rectangle].tl();
	m.unlock();


	cv::Mat Kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	// Filters
	cv::cvtColor(cropped_image, cropped_image, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(cropped_image, cropped_image, cv::Size(3, 3), 3, 0);
	cv::Canny(cropped_image, cropped_image, 50, 255);
	cv::dilate(cropped_image, cropped_image, Kernel);

	return cropped_image;
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
		//Approximation
		float peri = cv::arcLength(contours[i], true);
		cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
		
		//Searching rectangle
		if ((int)conPoly[i].size() == 4 && contourArea(contours[i]) > 3000)
		{
			areas[counter] = contourArea(contours[i]);
			counter++;
		}

		// Rysowanie konturów
		if((int)conPoly[i].size() == 4)
			cv::drawContours(image, conPoly, i, cv::Scalar(0, 255, 0), 1, cv::LINE_8, -1, 0, dxdy);
	}
	 //Wyswietlanie wartosci pól
	//std::cout << std::abs(areas[0] - areas[1]) << std::endl;

	//
	if (std::abs(areas[0] - areas[1]) > lower_value && std::abs(areas[0] - areas[1]) < upper_value)
	{
		cv::rectangle(image, boundRect, cv::Scalar(0, 255, 0), 5);
		return true;
	}
	else
	{
		cv::rectangle(image, boundRect, cv::Scalar(0, 0, 255), 5);
		return false;
	}
}
bool thread_vision::check_pattern_one_rect(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(input_image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	cv::Rect boundRect(dxdy, input_image.size());

	int area = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		//Approximation
		float peri = cv::arcLength(contours[i], true);
		cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);

		//Searching rectangle
		if ((int)conPoly[i].size() == 4 && contourArea(contours[i]) > 3000)
		{
			area = contourArea(contours[i]);
		}

		// Rysowanie konturów
		if ((int)conPoly[i].size() == 4)
			cv::drawContours(image, conPoly, i, cv::Scalar(0, 255, 0), 1, cv::LINE_8, -1, 0, dxdy);
	}
	//Wyswietlanie wartosci pól
	std::cout << area << std::endl;

	//
	if (std::abs(area) > lower_value && std::abs(area) < upper_value)
	{
		cv::rectangle(image, boundRect, cv::Scalar(0, 255, 0), 5);
		return true;
	}
	else
	{
		cv::rectangle(image, boundRect, cv::Scalar(0, 0, 255), 5);
		return false;
	}
}

void thread_vision::display_Tracksbars(int &hmin, int &hmax, int &smin, int &smax, int &vmin, int &vmax) {
	cv::Mat imageHSV;
	cv::Mat mask;
	cv::cvtColor(this->trackbars_img, imageHSV, cv::COLOR_BGR2GRAY);

	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
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
void thread_vision::init_boxes()
{
	m.lock();
	for (int i = 0; i < data_box.boxes.size(); i++)
	{
		if (i < 9)
		{
			cv::Point TL(data_box.boxes[i].getPosition().x - data_box.boxes[i].getSize().x / 2 + 10, data_box.boxes[i].getPosition().y + 30);
			cv::Point BR(data_box.boxes[i].getPosition().x + data_box.boxes[i].getSize().x / 2 + 40, data_box.boxes[i].getPosition().y + data_box.boxes[i].getSize().y / 2 + 30);
			boxes.push_back(cv::Rect(TL, BR));
		}
		else if (i == 9)
		{
			cv::Point TL(data_box.boxes[i].getPosition().x - data_box.boxes[i].getSize().x / 2, data_box.boxes[i].getPosition().y + 30);
			cv::Point BR(data_box.boxes[i].getPosition().x + data_box.boxes[i].getSize().x / 2 + 8, data_box.boxes[i].getPosition().y + data_box.boxes[i].getSize().y / 2 + 30);
			boxes.push_back(cv::Rect(TL, BR));
		}
		else if (i == 19)
		{
			cv::Point TL(data_box.boxes[i].getPosition().x - data_box.boxes[i].getSize().x / 2, data_box.boxes[i].getPosition().y + 65);
			cv::Point BR(data_box.boxes[i].getPosition().x + data_box.boxes[i].getSize().x / 2 + 8, data_box.boxes[i].getPosition().y + data_box.boxes[i].getSize().y / 2 + 65);
			boxes.push_back(cv::Rect(TL, BR));
		}
		else
		{
			cv::Point TL(data_box.boxes[i].getPosition().x - data_box.boxes[i].getSize().x / 2 + 10, data_box.boxes[i].getPosition().y + 65);
			cv::Point BR(data_box.boxes[i].getPosition().x + data_box.boxes[i].getSize().x / 2 + 40, data_box.boxes[i].getPosition().y + data_box.boxes[i].getSize().y / 2 + 65);
			boxes.push_back(cv::Rect(TL, BR));
		}

	}
	m.unlock();
}

void thread_vision::operator()(int index)
{
	//Initialization
	cv::VideoCapture camera(index);
	camera.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
	int hmin = 0, hmax = 179, smin = 0, smax = 255, vmin = 0, vmax = 255;



	while (true)
	{
		m.lock();
		if (data_box.is_sequence_activated != this->is_sequence_activated)
			this->is_sequence_activated = data_box.is_sequence_activated;
		m.unlock();

		if (this->is_sequence_activated)
		{
			if (boxes.size() == 0)
			{
				init_boxes();
			}
			

			// Camera trigger
			camera.read(image);
			cv::rotate(image, image, cv::ROTATE_180);

			cv::Mat red_button_image = button_filters(0);
			cv::Mat green_button_image = button_filters(1);

			if (check_pattern(red_button_image, cv::Point(50, 700), 500, 700))
				this->red_button = false;
			else
				this->red_button = true;

			if (check_pattern(green_button_image, cv::Point(1505, 705), 500, 700))
				this->green_button = false;
			else
				this->green_button = true;

			cv::Mat box = box_filters();

			this->box_detection = check_pattern_one_rect(box, TL_of_window, 5000, 7000);
			
			//  Communication between threads

			m.lock();

			if (data_box.green_button != this->green_button) 
				data_box.green_button = this->green_button;

			if (data_box.red_button != this->red_button) 
				data_box.red_button = this->red_button;

			if(data_box.detecting_box != this->box_detection)
				data_box.detecting_box = this->box_detection;

			m.unlock();

			//thread_vision::display_Tracksbars(hmin, hmax, smin, smax, vmin, vmax);

			//showing image
			//imshow("box", box);
			imshow("main", image);

			cv::waitKey(30);
		}
	}
}


