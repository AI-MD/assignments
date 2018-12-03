#pragma once

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace IPCVL {
	namespace EXAMPLE {
		void ChangeContrastAndBrightness(cv::InputArray src, cv::OutputArray dst, double alpha, int beta);
	} // namespace EXAMPLE
} // namespace IPCVL
