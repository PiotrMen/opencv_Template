#include "vision.h"

void thread_vision::operator()(int index)
{
	cv::VideoCapture camera(index);
	camera.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
	cv::Mat image, undistorted;
	cv::Mat CameraMatrix = (cv::Mat_<float>(3, 3) << 2257.4, 0, 624.0, 0, 2311.5, 646.2, 0, 0, 1);
	cv::Mat DistCoeffs = (cv::Mat_<float>(1, 5) << -0.75, 0.62, 0.0015, 0.0575, -0.86);
	cv::Mat map1, map2;
	cv::Mat newCamMatrix;
	cv::Mat Undistorted_remap;
	camera.read(image);
	cv::initUndistortRectifyMap(CameraMatrix, DistCoeffs, cv::Mat(), CameraMatrix, cv::Size(image.cols, image.rows), CV_32FC1, map1, map2);



	while (true)
	{
		camera.read(image);

		cv::remap(image, Undistorted_remap, map1, map2, cv::INTER_CUBIC);
		//cv::undistort(image, undistorted, CameraMatrix, DistCoeffs);


		//imshow("main" + index, image);

		//imshow("main2" + index, undistorted);
		imshow("main3" + index, Undistorted_remap);
		cv::waitKey(30);
	}
}