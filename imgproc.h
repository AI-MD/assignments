#pragma once

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace IPCVL {
	namespace IMG_PROC {
		void calcHist(cv::InputArray src, int* histogram);
		void calcHist_hs(cv::InputArray src, double histogram[][64]);
		void backprojectHistogram(cv::InputArray src_hsv, cv::InputArray face_hsv, cv::OutputArray dst);
	} // namespace IMG_PROC

	namespace UTIL {
		int quantize(int a);
		double h_r(double model_hist[][64], double input_hist[][64], int j, int i);
		void GetHistogramImage(int* histogram, cv::OutputArray dst, int hist_w, int hist_h);
	} // namespace UTIL

	namespace EXAMPLE {
		void ChangeContrastAndBrightness(cv::InputArray src, cv::OutputArray dst, double alpha, int beta);
	} // namespace EXAMPLE
} // namespace IPCVL
