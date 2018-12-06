#include "utils.h"

namespace IPCVL {
	namespace UTIL {
		int quantize(int a) {
			int L = 256;
			int q = 64;
			return floor((a * q) / L);
		}

		double h_r(double model_hist[][64], double input_hist[][64], int j, int i) {
			double h_m = model_hist[j][i];
			double h_i = input_hist[j][i];
			double val = 0.0;

			if (h_i == 0.0) return 1.0;
			else return (double)std::min(h_m / h_i, 1.0);
		}

		void GetHistogramImage(int* histogram, cv::OutputArray dst, int hist_w, int hist_h) {
			dst.create(cv::Size(hist_w, hist_h), CV_8UC1);
			cv::Mat histImage = dst.getMat();
			histImage.setTo(cv::Scalar(255, 255, 255));

			int bin_w = cvRound((double)hist_w / 256);

			// find the maximum intensity element from histogram
			int max = histogram[0];

			for (int i = 1; i < 256; i++)
				if (max < histogram[i]) max = histogram[i];

			// normalize the histogram between 0 and histImage.rows
			for (int i = 0; i < 255; i++)
				histogram[i] = ((double)histogram[i] / max) * histImage.rows;

			// draw the intensity line for histogram
			for (int i = 0; i < 255; i++)
				cv::line(histImage, cv::Point(bin_w*(i), hist_h), cv::Point(bin_w*(i), hist_h - histogram[i]), cv::Scalar(0, 0, 0), 1, 8, 0);
		}

		void calcNormedHist(cv::InputArray src, double* histogram) {
			cv::Mat inputMat = src.getMat();

			for (int y = 0; y < inputMat.rows; y++) {
				for (int x = 0; x < inputMat.cols; x++) {
					histogram[(int)inputMat.at<uchar>(y, x)]++;
				}
			}

			// normalize the histogram between 0 and histImage.rows
			for (int i = 0; i < 256; i++) {
					histogram[i] = (double)histogram[i] / (inputMat.rows * inputMat.cols);
			}
		}
	}  // namespace UTIL
}
