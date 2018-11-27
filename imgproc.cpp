#include "imgproc.h"

namespace IPCVL {
	namespace IMG_PROC {
		void calcHist(cv::InputArray src, int* histogram) {
			cv::Mat inputMat = src.getMat();

			for (int y = 0; y < inputMat.rows; y++) {
				for (int x = 0; x < inputMat.cols; x++) {
					// Todo : histogram을 쌓습니다. 

					/** your code here! **/

					// hint 1 : for loop 를 이용해서 cv::Mat 순회 시 (1채널의 경우) 
					// inputMat.at<uchar>(y, x)와 같이 데이터에 접근할 수 있습니다. 
				}
			}
		}
		void backprojectHistogram(cv::InputArray src_hsv, cv::InputArray face_hsv, cv::OutputArray dst) {
			cv::Mat srcMat = src_hsv.getMat();
			cv::Mat faceMat = face_hsv.getMat();
			dst.create(srcMat.size(), CV_64FC1);
			cv::Mat outputProb = dst.getMat();
			outputProb.setTo(cv::Scalar(0.));

			double model_hist[64][64] = { { 0., } };
			double input_hist[64][64] = { { 0., } };

			// Todo : hs 2차원 히스토그램을 계산하는 함수를 작성합니다. 
			calcHist_hs(srcMat, input_hist);
			calcHist_hs(faceMat, model_hist);

			for (int y = 0; y < srcMat.rows; y++) {
				for (int x = 0; x < srcMat.cols; x++) {
					// Todo : 양자화된 h,s 값을 얻고 histogram에 값을 더합니다. 

					/** your code here! **/

					// hint 1 : UTIL::quantize()를 이용해서 srtMat의 값을 양자화합니다. 
					// hint 2 : UTIL::h_r() 함수를 이용해서 outputPorb 값을 계산합니다. 
				}
			}
		}

		void calcHist_hs(cv::InputArray src_hsv, double histogram[][64]) {
			cv::Mat hsv = src_hsv.getMat();
			std::vector<cv::Mat> channels;
			split(hsv, channels);
			cv::Mat mat_h = channels[0];
			cv::Mat mat_s = channels[1];

			// 2차원 히스토그램을 쌓습니다. 
			for (int y = 0; y < hsv.rows; y++) {
				for (int x = 0; x < hsv.cols; x++) {
					// Todo : 양자화된 h,s 값을 얻고 histogram에 값을 더합니다. 

					/** your code here! **/

					// hint 1 : 양자화 시 UTIL::quantize() 함수를 이용해서 mat_h, mat_s의 값을 양자화시킵니다. 
				}
			}

			// 히스토그램을 (hsv.rows * hsv.cols)으로 정규화합니다. 
			for (int j = 0; j < 64; j++) {
				for (int i = 0; i < 64; i++) {
					// Todo : histogram에 있는 값들을 순회하며 (hsv.rows * hsv.cols)으로 정규화합니다. 
					/** your code here! **/
				}
			}
		}
	}  // namespace IMG_PROC

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
	}  // namespace UTIL

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

