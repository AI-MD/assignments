#include "imgproc.h"

namespace IPCVL {
	namespace IMG_PROC {
		void calcHist(cv::InputArray src, int* histogram) {
			cv::Mat inputMat = src.getMat();

			for (int y = 0; y < inputMat.rows; y++) {
				for (int x = 0; x < inputMat.cols; x++) {
					histogram[inputMat.at<uchar>(y, x)]++;
					//각 Mat에 Loop를 통하여 접근, Histogram 증가
				}
			}
		}
		void backprojectHistogram(cv::InputArray src_hsv, cv::InputArray face_hsv, cv::OutputArray dst) {
			cv::Mat srcMat = src_hsv.getMat();
			cv::Mat faceMat = face_hsv.getMat();
			dst.create(srcMat.size(), CV_64FC1);
			cv::Mat outputProb = dst.getMat();
			outputProb.setTo(cv::Scalar(0.)); // 배열의 전체를 0으로 변경

			std::vector<cv::Mat> channels;
			split(src_hsv, channels);
			cv::Mat mat_h = channels[0];
			cv::Mat mat_s = channels[1];

			double model_hist[64][64] = { { 0., } };
			double input_hist[64][64] = { { 0., } };

			// hs 2차원 히스토그램을 계산하는 함수.
			calcHist_hs(srcMat, input_hist);
			calcHist_hs(faceMat, model_hist);


			for (int y = 0; y < srcMat.rows; y++) {
				for (int x = 0; x < srcMat.cols; x++) {
					// Todo : 양자화된 h,s 값을 얻고 histogram에 값을 더합니다. 

					/** your code here! **/
					int h = UTIL::quantize(mat_h.at<uchar>(y, x));
					int s = UTIL::quantize(mat_s.at<uchar>(y, x));

					outputProb.at<double>(y, x) = UTIL::h_r(model_hist, input_hist, h, s);
				}
			}
		}

		void calcHist_hs(cv::InputArray src_hsv, double histogram[][64]) {
			cv::Mat hsv = src_hsv.getMat();
			std::vector<cv::Mat> channels;
			split(hsv, channels); //channels[0] 색상(H), 1 채도(S), 2 명도(V)
			cv::Mat mat_h = channels[0];
			cv::Mat mat_s = channels[1];

			// 2차원 히스토그램을 쌓습니다. 
			for (int y = 0; y < hsv.rows; y++) {
				for (int x = 0; x < hsv.cols; x++) {
					// Todo : 양자화된 h,s 값을 얻고 histogram에 값을 더합니다. 
					histogram[UTIL::quantize(mat_h.at<uchar>(y, x))][UTIL::quantize(mat_s.at<uchar>(y, x))]++;

					// hint 1 : 양자화 시 UTIL::quantize() 함수를 이용해서 mat_h, mat_s의 값을 양자화시킵니다. 
				}
			}

			// 히스토그램을 (hsv.rows * hsv.cols)으로 정규화합니다. 
			for (int j = 0; j < 64; j++) {
				for (int i = 0; i < 64; i++) {
					histogram[j][i] = histogram[j][i] / (hsv.rows * hsv.cols); // 모두 더하면 1
				}
			}
		}

		void thresh_binary(cv::InputArray src, cv::OutputArray dst, const int& threshold) {
			cv::Mat srcMat = src.getMat();
			dst.create(srcMat.size(), CV_8UC1);
			cv::Mat outputMat = dst.getMat();

			for (int y = 0; y < srcMat.rows; y++) {
				for (int x = 0; x < srcMat.cols; x++) {

					if (srcMat.at<uchar>(y, x) < threshold) {
						outputMat.at<uchar>(y, x) = 0;
					}
					else {
						outputMat.at<uchar>(y, x) = 255;
					}
				}
			}
		}

		void thresh_otsu(cv::InputArray src, cv::OutputArray dst) {

			cv::Mat srcMat = src.getMat();
			dst.create(srcMat.size(), CV_8UC1);
			cv::Mat outputMat = dst.getMat();
			outputMat.setTo(cv::Scalar(0.));

			double histogramNormalized[256] = { 0, };
			UTIL::calcNormedHist(src, histogramNormalized);

			double w[256] = { 0, },
				u0[256] = { 0, },
				u1[256] = { 0, },
				vBetween[256] = { 0, };

			double    u = 0.0,
				curMax = 0.0;
			int threshold = 0;

			for (int t = 0; t < 256; t++) {
				u += (t*histogramNormalized[t]);
			}

			w[0] = histogramNormalized[0];
			u0[0] = 0.0;

			for (int t = 1; t < 256; t++) {

				w[t] = w[t - 1] + histogramNormalized[t];

				if (w[t] == 0 || (1 - w[t]) == 0)
					continue;

				u0[t] = (w[t - 1] * u0[t - 1] + t * histogramNormalized[t]) / w[t];
				u1[t] = (u - w[t] * u0[t]) / (1 - w[t]);
				vBetween[t] = w[t] * (1 - w[t]) * (pow(u0[t] - u1[t], 2));

				if (vBetween[t] > curMax) {
					curMax = vBetween[t];
					threshold = t;
				}
			}
			thresh_binary(srcMat, outputMat, threshold);
			
		}

		void flood_fill4(cv::Mat& l, const int& j, const int& i, const int& label) {
			if (l.at<int>(j, i) == -1) {
				l.at<int>(j, i) = label;
				flood_fill4(l, j, i + 1, label);
				flood_fill4(l, j - 1, i, label);
				flood_fill4(l, j, i - 1, label);
				flood_fill4(l, j + 1, i, label);
			}
		}

		void flood_fill8(cv::Mat& l, const int& j, const int& i, const int& label) {
			if (l.at<int>(j, i) == -1) {
				l.at<int>(j, i) = label;

				flood_fill8(l, j, i + 1, label);
				flood_fill8(l, j - 1, i, label);
				flood_fill8(l, j, i - 1, label);
				flood_fill8(l, j + 1, i, label);
				flood_fill8(l, j - 1, i + 1, label);
				flood_fill8(l, j - 1, i - 1, label);
				flood_fill8(l, j + 1, i - 1, label);
				flood_fill8(l, j + 1, i + 1, label);
			}
		}
		void flood_fill(cv::InputArray src, cv::OutputArray dst, const UTIL::CONNECTIVITIES& direction) {
			cv::Mat srcMat = src.getMat();
			dst.create(srcMat.size(), CV_32SC1);
			cv::Mat outputMat = dst.getMat();
			outputMat.setTo(cv::Scalar(0.));

			for (int j = 0; j < srcMat.rows; j++) {
				for (int i = 0; i < srcMat.cols; i++) {
					if (j == 0 || j == srcMat.rows - 1 || i == 0 || i == srcMat.cols - 1) {
						outputMat.at<int>(j, i) = 0;
					}
					else if (srcMat.at<uchar>(j, i) != 0) {
						outputMat.at<int>(j, i) = -1;
					}
					else {
						outputMat.at<int>(j, i) = 0;
					}
				}
			}

			int label = 1;

			for (int j = 1; j < srcMat.rows - 1; j++) {
				for (int i = 1; i < srcMat.cols - 1; i++) {
					if (outputMat.at<int>(j, i) == -1) {
						switch (direction) {
						case UTIL::CONNECTIVITIES::EFFICIENT_FOURWAY:
							efficient_flood_fill4(outputMat, j, i, label);
							label++;
							break;

						case UTIL::CONNECTIVITIES::NAIVE_EIGHT_WAY:
							flood_fill8(outputMat, j, i, label);
							label++;
							break;

						case UTIL::CONNECTIVITIES::NAIVE_FOURWAY:
							flood_fill4(outputMat, j, i, label);
							label++;
							break;
						}
					}
				}
			}

		}
		void efficient_flood_fill4(cv::Mat& l, const int& j, const int& i, const int& label) {
			int left, right, y, x;
			std::queue< std::pair<int, int> > q;
			q.push(std::make_pair(j, i));

			while (!q.empty()) {

				std::pair<int, int> pair = q.front();

				y = pair.first;
				x = pair.second;

				q.pop();
				if (l.at<int>(y, x) == -1) {
					left = right = x;
					while (l.at<int>(y, left - 1) == -1) left--;

					while (l.at<int>(y, right + 1) == -1) right++;

					for (int c = left; c <= right; c++) {
						l.at<int>(y, c) = label;

						if (l.at<int>(y - 1, c) == -1 && (c == left || l.at<int>(y - 1, c - 1) != -1))
							q.push(std::make_pair(y - 1, c));
						if (l.at<int>(y + 1, c) == -1 && (c == left || l.at<int>(y + 1, c - 1) != -1))
							q.push(std::make_pair(y + 1, c));
					}
				}
			}
		}
	

	}  // namespace IMG_PROC
}