#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat inputImage;
	inputImage = imread("samples/sample.jpg");
	imshow("sample", inputImage);
	waitKey(0);
	return 0;
}