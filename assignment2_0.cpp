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
	cv::Mat srcMat = cv::imread("./samples/sample2_0.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat opencvResult, ourResult;
	const int THRESHOLD = 125;

	cv::threshold(srcMat, opencvResult, THRESHOLD, 255, cv::THRESH_BINARY);
	IPCVL::IMG_PROC::thresh_binary(srcMat, ourResult, THRESHOLD);

	//Sanity Check
	cv::Mat diff = cv::abs(ourResult / 255 - opencvResult / 255);
	double error = cv::sum(diff)[0] / (srcMat.cols * srcMat.rows);
	std::cout << "error: " << error << std::endl;
	floorf(error * 100) / 100 == 0 ? std::cout << "PASS!!!" << std::endl : std::cout << "FAIL..." << std::endl;

	//Show Result
	cv::imshow("Input Image", srcMat);
	cv::imshow("Opencv Result", opencvResult);
	cv::imshow("Our Result", ourResult);
	cv::waitKey();

	return 0;
}