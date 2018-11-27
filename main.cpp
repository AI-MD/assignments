#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "imgproc.h"

int main() {
	cv::Mat sampleImage = cv::imread("samples/hee.jpg");
	cv::Mat input = cv::imread("samples/hee.jpg");
	cv::Mat face = cv::imread("samples/face.png");
	cv::Mat src_hsv, face_hsv;
	cvtColor(input, src_hsv, cv::COLOR_BGR2HSV);
	cvtColor(face, face_hsv, cv::COLOR_BGR2HSV);
	cv::Mat output;
	IPCVL::IMG_PROC::backprojectHistogram(src_hsv, face_hsv, output);

	imshow("IU", input);
	imshow("face", face);
	imshow("output", output);
	cv::waitKey(0);
	/*
	Mat inputImage, outputImage;
	inputImage = imread("samples/lena.bmp", IMREAD_GRAYSCALE);

	double alpha = 1.1;
	int beta = 50;
	IPCVL::ChangeContrastAndBrightness(inputImage, outputImage, alpha, beta);

	int inputHistogram[256] = { 0, };
	int outputHhistogram[256] = { 0, };

	IPCVL::calcHist(inputImage, inputHistogram);
	IPCVL::calcHist(outputImage, outputHhistogram);

	cv::Mat inputHistImage;
	cv::Mat outputHistImage;

	int hist_w = 512, hist_h = 400;
	IPCVL::GetHistogramImage(inputHistogram, inputHistImage, hist_w, hist_h);
	IPCVL::GetHistogramImage(outputHhistogram, outputHistImage, hist_w, hist_h);
	
	// display
	imshow("inputImage", inputImage);
	imshow("outputImage", outputImage);
	imshow("inputImage Histogram", inputHistImage);
	imshow("outputImage Histogram", outputHistImage);
	waitKey(0);
	*/
	return 0;
}