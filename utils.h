#pragma once

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace IPCVL {
	namespace UTIL {
		enum CONNECTIVITIES {
			NAIVE_FOURWAY = 0,
			NAIVE_EIGHT_WAY,
			EFFICIENT_FOURWAY
		};
		int quantize(int a);
		double h_r(double model_hist[][64], double input_hist[][64], int j, int i);
		void GetHistogramImage(int* histogram, cv::OutputArray dst, int hist_w, int hist_h);
		void calcNormedHist(cv::InputArray src, double* histogram);
	} // namespace UTIL
} // namespace IPCVL
