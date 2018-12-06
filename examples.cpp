#include "examples.h"

namespace IPCVL {
	namespace EXAMPLE {
		void ChangeContrastAndBrightness(cv::InputArray src, cv::OutputArray dst, double alpha, int beta) {
			dst.create(src.size(), src.type());
			cv::Mat inputMat = src.getMat();
			cv::Mat outputMat = dst.getMat();

			for (int y = 0; y < inputMat.rows; y++)
				for (int x = 0; x < inputMat.cols; x++)
					outputMat.at<uchar>(y, x) = cv::saturate_cast<uchar>(alpha * inputMat.at<uchar>(y, x) + beta);
		}
	}  // namespace EXAMPLE
}

