/* Assignment #1 */

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "imgproc.h"
#include "utils.h"
#include "examples.h"

int main() {
	cv::Mat inputImage, outputImage;
	inputImage = cv::imread("samples/lena.bmp", cv::IMREAD_GRAYSCALE);

	double alpha = 1.1;
	int beta = 50;
	IPCVL::EXAMPLE::ChangeContrastAndBrightness(inputImage, outputImage, alpha, beta);

	int inputHistogram[256] = { 0, };
	int outputHhistogram[256] = { 0, };

	// Todo : imageproc.cpp에 있는 calcHist 함수를 작성하세요
	IPCVL::IMG_PROC::calcHist(inputImage, inputHistogram); 
	IPCVL::IMG_PROC::calcHist(outputImage, outputHhistogram);

	cv::Mat inputHistImage;
	cv::Mat outputHistImage;

	int hist_w = 512, hist_h = 400;
	IPCVL::UTIL::GetHistogramImage(inputHistogram, inputHistImage, hist_w, hist_h);
	IPCVL::UTIL::GetHistogramImage(outputHhistogram, outputHistImage, hist_w, hist_h);

	// display
	cv::imshow("inputImage", inputImage);
	cv::imshow("outputImage", outputImage);
	cv::imshow("inputImage Histogram", inputHistImage);
	cv::imshow("outputImage Histogram", outputHistImage);
	cv::waitKey(0);
}