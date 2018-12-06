/* Assignment #0 */

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "imgproc.h" //-->> It should be Changed 
#include "utils.h"
#include "examples.h"

int main() {
	cv::Mat src_small = cv::imread("./samples/sample2_2_1.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat src_big = cv::imread("./samples/sample2_2_2.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat result_naive_4, result_naive_8, result_efficient_4;

	cv::namedWindow("small src Image", cv::WINDOW_NORMAL);
	cv::namedWindow("small image naive 4-way", cv::WINDOW_NORMAL);
	cv::namedWindow("small image naive 8-way", cv::WINDOW_NORMAL);

	cv::resizeWindow("small src Image", 640, 640);
	cv::resizeWindow("small image naive 4-way", 640, 640);
	cv::resizeWindow("small image naive 8-way", 640, 640);

	IPCVL::IMG_PROC::flood_fill(src_small, result_naive_4, IPCVL::UTIL::CONNECTIVITIES::NAIVE_FOURWAY);
	IPCVL::IMG_PROC::flood_fill(src_small, result_naive_8, IPCVL::UTIL::CONNECTIVITIES::NAIVE_EIGHT_WAY);
	IPCVL::IMG_PROC::flood_fill(src_big, result_efficient_4, IPCVL::UTIL::CONNECTIVITIES::EFFICIENT_FOURWAY);

	double min, max;

	cv::minMaxLoc(result_naive_4, &min, &max);
	result_naive_4.convertTo(result_naive_4, CV_32FC1, 1 / max);

	cv::minMaxLoc(result_naive_8, &min, &max);
	result_naive_8.convertTo(result_naive_8, CV_32FC1, 1 / max);

	cv::minMaxLoc(result_efficient_4, &min, &max);
	result_efficient_4.convertTo(result_efficient_4, CV_32FC1, 1 / max);

	//Show Result
	cv::imshow("small src Image", src_small);
	cv::imshow("big src Image", src_big);
	cv::imshow("small image naive 4-way", result_naive_4);
	cv::imshow("small image naive 8-way", result_naive_8);
	cv::imshow("big image efficient 4-way", result_efficient_4);
	cv::waitKey();

	return 0;
}