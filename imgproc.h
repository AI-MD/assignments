#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace IPCVL
{

	void ChangeContrastAndBrightness(cv::InputArray src, cv::OutputArray dst, double alpha, int beta);
}
