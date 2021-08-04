#include "vision.h"


cv::Mat thread_vision::button_filters() 
{
	cv::Mat cropped_image;
	cv::Mat hist_image;
	cv::Mat Kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));

		// Cropping image
		cv::Rect crop_region(1605, 805, 315, 275);
		cropped_image = image(crop_region);
		cv::MatND histogram;
		int histSize = 256;
		const int* channel_numbers = {0};
		float channel_range[] = {0.0,256.0};
		const float* channel_ranges = channel_range;
		int number_bins = histSize;

		

		// Filters
		cv::cvtColor(cropped_image, cropped_image, cv::COLOR_BGR2GRAY);


		hist_image = cropped_image;
		cv::calcHist(&hist_image, 1, 0, cv::Mat(), histogram, 1, &number_bins, &channel_ranges);

		int hist_w = 512, hist_h = 400;
		int bin_w = cvRound((double)hist_w / histSize);
		cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
		normalize(histogram, histogram, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
		for (int i = 1; i < histSize; i++)
		{
			line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
				cv::Point(bin_w*(i), hist_h - cvRound(histogram.at<float>(i))),
				cv::Scalar(255, 0, 0), 2, 8, 0);
		}
		//cv::imshow("Source image", cropped_image);
	//	imshow("calcHist Demo", histImage);
		cv::waitKey(1);

		cv::GaussianBlur(cropped_image, cropped_image, cv::Size(3, 3), 3, 0);
		cv::Canny(cropped_image, cropped_image, 50, 255);
		cv::dilate(cropped_image, cropped_image, Kernel);

		//Pomocnicze trackbary
		//cv::namedWindow("Trackbars", (640, 200));
		//cv::createTrackbar("Tresh Min", "Trackbars", &tresh_min, 255);
		//cv::createTrackbar("Tresh Max", "Trackbars", &tresh_max, 255);

		//Wyswietlanie pomocnicze
		//imshow("Przycisk" + std::to_string(select_button), cropped_image);

		return cropped_image;
}
cv::Mat thread_vision::button_filter()
{
	cv::Mat cropped_image;
	cv::Mat mask;
	cv::Mat hist_image;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::Mat kerneldil = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(6, 6));


	// Cropping image
	cv::Rect crop_region(1605, 805, 315, 275);
	cropped_image = image(crop_region);
	//cv::MatND histogram;

	cv::Scalar lower(148, 230, 55);
	cv::Scalar upper(244, 255, 239);
	cv::inRange(cropped_image, lower, upper, mask);

	cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
	cv::dilate(mask, mask, kerneldil);

	imshow("mask1", mask);


	//int histSize = 256;
	//const int* channel_numbers = { 0 };
	//float channel_range[] = { 0.0,256.0 };
	//const float* channel_ranges[] = { channel_range };
	//int number_bins = histSize;

	//std::vector<cv::Mat> bgr_image;
	//cv::split(cropped_image, bgr_image);

	//// Filters
	//hist_image = cropped_image;

	//bool uniform = true, accumulate = false;
	//cv::Mat b_hist, g_hist, r_hist;
	//calcHist(&bgr_image[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, channel_ranges, uniform, accumulate);
	//calcHist(&bgr_image[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, channel_ranges, uniform, accumulate);
	//calcHist(&bgr_image[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, channel_ranges, uniform, accumulate);

	//int hist_w = 512, hist_h = 400;
	//int bin_w = cvRound((double)hist_w / histSize);
	//cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
	//normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	//normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	//normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

	//for (int i = 1; i < histSize; i++)
	//{
	//	line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
	//		cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
	//		cv::Scalar(255, 0, 0), 2, 8, 0);
	//	line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
	//		cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
	//		cv::Scalar(0, 255, 0), 2, 8, 0);
	//	line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
	//		cv::Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
	//		cv::Scalar(0, 0, 255), 2, 8, 0);
	//}
	//cv::imshow("Source image", cropped_image);
	//imshow("calcHist Demo", histImage);
	//cv::waitKey(1);


	return mask;
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

bool thread_vision::check_pattern_circle(cv::Mat input_image, cv::Point dxdy, int lower_value, int upper_value)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(input_image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	cv::Rect boundRect(dxdy, input_image.size());

	int area = 0;
	int counter = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		//Approximation
		float peri = cv::arcLength(contours[i], true);
		cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);

		//Searching rectangle
		if ((int)conPoly[i].size() == 8 && contourArea(contours[i]) > 3000)
		{
			if(area<contourArea(contours[i]))
				area = contourArea(contours[i]);
		}

		// Rysowanie konturów
		if ((int)conPoly[i].size() == 8)
			cv::drawContours(image, conPoly, i, cv::Scalar(0, 255, 0), 1, cv::LINE_8, -1, 0, dxdy);
	}
	//Wyswietlanie wartosci pól
   std::cout << area << std::endl;

	if (area > lower_value && area < upper_value)
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

cv::Mat thread_vision::getWarp(cv::Mat img, std::vector<cv::Point> points, float w, float h) {
	cv::Mat imgWarp;
	cv::Point2f src[4] = { points[0],points[1],points[2],points[3] };
	cv::Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
	cv::warpPerspective(img, imgWarp, matrix, cv::Point(w, h));

	return imgWarp;
}

std::vector<cv::Point> thread_vision::reorder(std::vector<cv::Point> points) {
	std::vector<cv::Point> newPoints;
	std::vector<int> sumPoints, subPoints;

	for (int i = 0; i < 4; i++) {
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

	return newPoints;
}

std::vector<cv::Point> thread_vision::find_contours_for_calib(cv::Mat mask) {
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());

	int area_max= 0;
	int index = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		//Approximation
		float peri = cv::arcLength(contours[i], true);
		cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);

		//Searching rectangle
		if ((int)conPoly[i].size() == 4 && contourArea(contours[i]) > area_max)
		{
			area_max = contourArea(contours[i]);
			index = i;
		}
	}

	// Rysowanie konturów
	if ((int)conPoly[index].size() == 4)
		cv::drawContours(image, conPoly, index, cv::Scalar(0, 255, 0), 1, cv::LINE_8, -1, 0);

	return conPoly[index];
}

std::vector<cv::Point> thread_vision::image_calibration(cv::VideoCapture cam) {
	cam.read(this->image);
	cv::rotate(this->image, this->image, cv::ROTATE_180);
	cv::Mat img_filtered;
	int hmin = 0;
	int hmax = 179;
	int smin = 0;
	int smax = 69;
	int vmin = 202;
	int vmax = 255;
	cv::Mat mask;
	cv::Mat Kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	// Filters
	cv::cvtColor(this->image, img_filtered, cv::COLOR_BGR2HSV);
	cv::GaussianBlur(img_filtered, img_filtered, cv::Size(3, 3), 3, 0);
	cv::Scalar lower(hmin, smin, vmin);
	cv::Scalar upper(hmax, smax, vmax);
	cv::inRange(img_filtered, lower, upper, mask);

	cv::Canny(mask, mask, 0, 255);
	cv::dilate(mask, mask, Kernel);


	std::vector<cv::Point> coordinates = find_contours_for_calib(mask);
	std::vector<cv::Point> coordinates_reordered = reorder(coordinates);
	cv::waitKey(33);
	return coordinates_reordered;
}

void thread_vision::display_Tracksbars(int &hmin, int &hmax, int &smin, int &smax, int &vmin, int &vmax) {
	cv::Mat imageHSV;
	cv::Mat mask;
	//cv::cvtColor(this->trackbars_img, imageHSV, cv::COLOR_BGR2GRAY);

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
			cv::Point TL(data_box.boxes[i].getPosition().x - data_box.boxes[i].getSize().x / 2, data_box.boxes[i].getPosition().y + 215);
			cv::Point BR(data_box.boxes[i].getPosition().x + data_box.boxes[i].getSize().x / 2 + 10, data_box.boxes[i].getPosition().y + data_box.boxes[i].getSize().y / 2 + 130);
			boxes.push_back(cv::Rect(TL, BR));
		}
		else if (i == 9)
		{
			cv::Point TL(data_box.boxes[i].getPosition().x - data_box.boxes[i].getSize().x / 2, data_box.boxes[i].getPosition().y + 130);
			cv::Point BR(data_box.boxes[i].getPosition().x + data_box.boxes[i].getSize().x / 2, data_box.boxes[i].getPosition().y + data_box.boxes[i].getSize().y / 2 + 130);
			boxes.push_back(cv::Rect(TL, BR));
		}

	}
	m.unlock();
}

void thread_vision::set_warp_parameters(float w, float h)
{
	// do testow
	cv::Point2f src[4] = { coordinates_reordered[0],coordinates_reordered[1],coordinates_reordered[2],coordinates_reordered[3] };
	cv::Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	cv::Mat transformationMatrix = cv::getPerspectiveTransform(src, dst);

	// Since the camera won't be moving, let's pregenerate the remap LUT
	cv::Mat inverseTransMatrix;
	cv::invert(transformationMatrix, inverseTransMatrix);

	// Generate the warp matrix
	cv::Mat map_x, map_y, srcTM;
	srcTM = inverseTransMatrix.clone(); // If WARP_INVERSE, set srcTM to transformationMatrix

	map_x.create(image.size(), CV_32FC1);
	map_y.create(image.size(), CV_32FC1);

	double M11, M12, M13, M21, M22, M23, M31, M32, M33;
	M11 = srcTM.at<double>(0, 0);
	M12 = srcTM.at<double>(0, 1);
	M13 = srcTM.at<double>(0, 2);
	M21 = srcTM.at<double>(1, 0);
	M22 = srcTM.at<double>(1, 1);
	M23 = srcTM.at<double>(1, 2);
	M31 = srcTM.at<double>(2, 0);
	M32 = srcTM.at<double>(2, 1);
	M33 = srcTM.at<double>(2, 2);

	for (int y = 0; y < image.rows; y++) {
		double fy = (double)y;
		for (int x = 0; x < image.cols; x++) {
			double fx = (double)x;
			double w = ((M31 * fx) + (M32 * fy) + M33);
			w = w != 0.0f ? 1.f / w : 0.0f;
			float new_x = (float)((M11 * fx) + (M12 * fy) + M13) * w;
			float new_y = (float)((M21 * fx) + (M22 * fy) + M23) * w;
			map_x.at<float>(y, x) = new_x;
			map_y.at<float>(y, x) = new_y;
		}
	}

	// This creates a fixed-point representation of the mapping resulting in ~4% CPU savings
	//cv::Mat transformation_x, transformation_y;
	this->transformation_x.create(image.size(), CV_16SC2);
	this->transformation_y.create(image.size(), CV_16UC1);
	cv::convertMaps(map_x, map_y, this->transformation_x, this->transformation_y, false);

	// If the fixed-point representation causes issues, replace it with this code
	//transformation_x = map_x.clone();
	//transformation_y = map_y.clone();
}

void thread_vision::operator()(int index)
{
	//Initialization
	cv::VideoCapture camera(index);
	camera.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
	int hmin = 0, hmax = 179, smin = 0, smax = 255, vmin = 0, vmax = 255;

	load_table_coordinates(this->coordinates_reordered);

	camera.read(image);
	cv::rotate(image, image, cv::ROTATE_180);
	set_warp_parameters(1920, 1080);

	// Do testowania bez ekranu

	//while (true)
	//{
	//	// Camera trigger
	//	camera.read(image);
	//	cv::rotate(image, image, cv::ROTATE_180);
	//	cv::remap(image, image, transformation_x, transformation_y, cv::INTER_CUBIC);  // INTER_NEAREST oko³o 20ms // INTER_CUBIC okolo 120ms  //INTER_LANCZOS4 okolo 240ms
	//	//this->image = getWarp(this->image, coordinates_reordered, 1920, 1080);
	//	cv::Mat green_button_image = button_filters();
	//	imshow("main", image);
	//	cv::waitKey(1);
	//}

	while (true)
	{
		sf::Clock clock2; // starts the clock

		if (data_box.camera_calibration) {
			this->calibration_flag = data_box.camera_calibration;
			this->coordinates_reordered = image_calibration(camera);
		}
		if (this->calibration_flag && !data_box.camera_calibration) {
			save_table_coordinates(this->coordinates_reordered);
			load_table_coordinates(this->coordinates_reordered);
			set_warp_parameters(1920, 1080);
			this->calibration_flag = false;
		}

		m.lock();
		if (data_box.is_sequence_activated != this->is_sequence_activated)
			this->is_sequence_activated = data_box.is_sequence_activated;
		m.unlock();

		if (!this->timer_flag) {
			m.lock();
			data_box.real_time_calibration_camera = this->clock.getElapsedTime();

			if (data_box.real_time_calibration_camera >= this->time_calibration_camera) {
				this->timer_flag = true;
				data_box.timer_done = true;
			}
			m.unlock();
		}


		if (this->is_sequence_activated && this->timer_flag)
		{
			if (boxes.size() == 0)
			{
				init_boxes();
			}
			
			// Camera trigger
			camera.read(image);
			cv::rotate(image, image, cv::ROTATE_180);
			cv::remap(image, image, transformation_x, transformation_y, cv::INTER_CUBIC); // INTER_NEAREST oko³o 20ms // INTER_CUBIC okolo 120ms  //INTER_LANCZOS4 okolo 240ms
		//	this->image = getWarp(this->image, coordinates_reordered, 1920, 1080);
			cv::Mat green_button_image = button_filter();

			//download detection section
			if (this->box_flag) { 
				this->real_time = this->clock.getElapsedTime();
				if (this->real_time >= this->time_compare) {
					this->box_flag = false;
					this->clock.restart();
					this->real_time = this->clock.restart();
				}
			}

			////additional secure
			if (!this->box_flag && data_box.step_in_sequence == 2) {
				if (check_pattern_circle(green_button_image, cv::Point(1605, 805), 9000, 14000))
					this->green_button = false;
				else {
					this->green_button = true;
					this->clock.restart();
				}
			}


			m2.lock();
			if(sequence.size()!=0)
				this->box = box_filters();
			m2.unlock();

			////boxes detection
			if (data_box.step_in_sequence == 1) {
				if (check_pattern_one_rect(this->box, TL_of_window, 5000, 7000))
					this->box_detection = false;
				else {
					this->box_detection = true;
					this->box_flag = true;
					this->clock.restart();
				}
			}


			//accept button detection
			if (this->green_button && this->box_detection) {
				this->green_button = false;
				this->box_detection = false;
			}

			////  Communication between threads

			//m.lock();

			//if (data_box.green_button != this->green_button) 
			//	data_box.green_button = this->green_button;

			//if(data_box.detecting_box != this->box_detection)
			//	data_box.detecting_box = this->box_detection;

			//m.unlock();

			//thread_vision::display_Tracksbars(hmin, hmax, smin, smax, vmin, vmax);

			//showing image
		//	imshow("box", box);
			imshow("green", green_button_image);
			imshow("main", image);

			cv::waitKey(1);
		}
		else
			cv::destroyAllWindows();

		//exit program variable
		if (data_box.global_exit)
			break;
		sf::Time elapsed1 = clock2.getElapsedTime();
		std::cout << elapsed1.asMilliseconds() << std::endl;
		clock2.restart();
	}
}


