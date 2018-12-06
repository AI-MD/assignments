#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "imgproc.h"
#include "utils.h"
#include "examples.h"

int main() {
	cv::Mat input = cv::imread("samples/sample1.png");
	cv::Mat face = cv::imread("samples/face.png");

	cv::Mat src_hsv, face_hsv;
	cvtColor(input, src_hsv, cv::COLOR_BGR2HSV);
	cvtColor(face, face_hsv, cv::COLOR_BGR2HSV);

	cv::Mat output;
	// Todo : imageproc.cpp에 있는 backprojectHistogram 함수를 작성하세요
	IPCVL::IMG_PROC::backprojectHistogram(src_hsv, face_hsv, output);

	// display
	imshow("input", input);
	imshow("face", face);
	imshow("model output", output);
	cv::waitKey(0);

	return 0;
}