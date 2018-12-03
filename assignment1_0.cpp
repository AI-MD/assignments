/* Assignment #0 */

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

	// display
	imshow("inputImage", inputImage);
	imshow("outputImage", outputImage);
	cv::waitKey(0);

	return 0;
}