#include "imgproc.h"
using namespace cv;

namespace IPCVL
{
	void ChangeContrastAndBrightness(cv::InputArray src, cv::OutputArray dst, double alpha, int beta) 
	{
		dst.create(src.size(), src.type());
		Mat inputMat = src.getMat();
		Mat outputMat = dst.getMat();

		for (int y = 0; y < inputMat.rows; y++) 
		{
			for (int x = 0; x < inputMat.cols; x++) 
			{
				outputMat.at<uchar>(y, x) = saturate_cast<uchar>(alpha * inputMat.at<uchar>(y, x) + beta);
			} // x
		} // y
	}
}

