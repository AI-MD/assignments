#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "imgproc.h"

using namespace cv;
using namespace std;

int main() {
	Mat inputImage;
	inputImage = imread("samples/lena.bmp", IMREAD_GRAYSCALE);

	Mat outputImage;
	IPCVL::ChangeContrastAndBrightness(inputImage, outputImage, 1, 15);

	imshow("original Image", inputImage);
	imshow("dst Image", outputImage);
	waitKey(0);

	return 0;
}