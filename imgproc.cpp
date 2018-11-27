#include "imgproc.h"

namespace IPCVL {
	namespace IMG_PROC {
		void calcHist(cv::InputArray src, int* histogram) {
			cv::Mat inputMat = src.getMat();

			for (int y = 0; y < inputMat.rows; y++) {
				for (int x = 0; x < inputMat.cols; x++) {
					// Todo : histogram�� �׽��ϴ�. 

					/** your code here! **/

					// hint 1 : for loop �� �̿��ؼ� cv::Mat ��ȸ �� (1ä���� ���) 
					// inputMat.at<uchar>(y, x)�� ���� �����Ϳ� ������ �� �ֽ��ϴ�. 
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

			// Todo : hs 2���� ������׷��� ����ϴ� �Լ��� �ۼ��մϴ�. 
			calcHist_hs(srcMat, input_hist);
			calcHist_hs(faceMat, model_hist);

			for (int y = 0; y < srcMat.rows; y++) {
				for (int x = 0; x < srcMat.cols; x++) {
					// Todo : ����ȭ�� h,s ���� ��� histogram�� ���� ���մϴ�. 

					/** your code here! **/

					// hint 1 : UTIL::quantize()�� �̿��ؼ� srtMat�� ���� ����ȭ�մϴ�. 
					// hint 2 : UTIL::h_r() �Լ��� �̿��ؼ� outputPorb ���� ����մϴ�. 
				}
			}
		}

		void calcHist_hs(cv::InputArray src_hsv, double histogram[][64]) {
			cv::Mat hsv = src_hsv.getMat();
			std::vector<cv::Mat> channels;
			split(hsv, channels);
			cv::Mat mat_h = channels[0];
			cv::Mat mat_s = channels[1];

			// 2���� ������׷��� �׽��ϴ�. 
			for (int y = 0; y < hsv.rows; y++) {
				for (int x = 0; x < hsv.cols; x++) {
					// Todo : ����ȭ�� h,s ���� ��� histogram�� ���� ���մϴ�. 

					/** your code here! **/

					// hint 1 : ����ȭ �� UTIL::quantize() �Լ��� �̿��ؼ� mat_h, mat_s�� ���� ����ȭ��ŵ�ϴ�. 
				}
			}

			// ������׷��� (hsv.rows * hsv.cols)���� ����ȭ�մϴ�. 
			for (int j = 0; j < 64; j++) {
				for (int i = 0; i < 64; i++) {
					// Todo : histogram�� �ִ� ������ ��ȸ�ϸ� (hsv.rows * hsv.cols)���� ����ȭ�մϴ�. 
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

