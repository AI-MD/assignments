#include "imgproc.h"

namespace IPCVL {
	namespace IMG_PROC {
		void thresh_otsu(cv::InputArray src, cv::OutputArray dst) {
			dst.create(src.size(), CV_8UC1);
			cv::Mat inputMat = src.getMat();
			cv::Mat outputMat = dst.getMat();
			double histogram[256];
			int i, y, x;
			double w[256], u0[256], u1[256], prob[256];
			double vBetween[256], max_sigma,u;
			int threshold;
			/*������׷� ���  */
			for (i = 0; i < 256; i++) histogram[i] = 0;
			for (y = 0; y < inputMat.rows; y++)
				for (x = 0; x < inputMat.cols; x++) {
					histogram[(int)inputMat.at<uchar>(y, x)]++;
				}
			/*������׷� ����ȭ*/
			for (i = 0; i < 256; i++) {
				prob[i] = (double)histogram[i] / (inputMat.rows * inputMat.cols);
			}
			
			u = 0.0;
			/*������׷� ��Ȱȭ*/
			for (int k = 0; k < 256; k++) {
				u += (k*prob[k]);
				
			}
			/* ����˰��� �л� �ִ� */
			
			u0[0] = 0.0;
			w[0] = prob[0];
			threshold = 0;
			max_sigma = 0.0;
			for (i = 1; i < 256; i++) {
				w[i] = w[i - 1] + prob[i];
				
				if (w[i] == 0.0 || (1-w[i]) == 0.0)
					continue;

				u0[i] = (w[i - 1]* u0[i - 1] + i * prob[i])/w[i];
				u1[i] = (u - w[i] * u0[i]) / (1 - w[i]);
				vBetween[i] = w[i] * (1 - w[i])* pow(u0[i] - u1[i], 2);
					
				
				if (vBetween[i] > max_sigma) {
					max_sigma = vBetween[i];
					threshold = i;
				}
			}


			thresh_binary(inputMat, outputMat, threshold);
			
		}


		void thresh_binary(cv::InputArray srcMat, cv::OutputArray ourResult, const int THRESHOLD) {
			ourResult.create(srcMat.size(), CV_8UC1);
			cv::Mat inputMat = srcMat.getMat();
			cv::Mat outputMat = ourResult.getMat();

			for (int y = 0; y < inputMat.rows; y++) {
				for (int x = 0; x < inputMat.cols; x++) {
					if (inputMat.at<uchar>(y, x) > THRESHOLD)
						outputMat.at<uchar>(y, x) = 255;
					else if (inputMat.at<uchar>(y, x) <THRESHOLD)
						outputMat.at<uchar>(y, x) = 0;
				}
			}

		}



		void calcHist(cv::InputArray src, int* histogram) {
			cv::Mat inputMat = src.getMat();

			for (int y = 0; y < inputMat.rows; y++) {
				for (int x = 0; x < inputMat.cols; x++) {

					histogram[(int)inputMat.at<uchar>(y, x)] = histogram[(int)inputMat.at<uchar>(y, x)] + 1;

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
			//dst.create(srcMat.size(), CV_64FC1);
			dst.create(srcMat.size(), CV_8UC1);

			std::vector<cv::Mat> channels;
			split(src_hsv, channels);
			cv::Mat src_h = channels[0];
			cv::Mat src_s = channels[1];


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

					int srcQuantH = UTIL::quantize(src_h.at<uchar>(y, x));
					int srcQuantS = UTIL::quantize(src_s.at<uchar>(y, x));

					int val = (UTIL::h_r(model_hist, input_hist, srcQuantH, srcQuantS) * 255);

					if (val > 255)
						val = 255;
					if (val < 0)
						val = 0;
					outputProb.at<uchar>(y, x) = val;
					// hint 1 : UTIL::quantize()�� �̿��ؼ� srctMat�� ���� ����ȭ�մϴ�. 
					// hint 2 : UTIL::h_r() �Լ��� �̿��ؼ� outputProb ���� ����մϴ�. 


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
					int qunantH = (int)UTIL::quantize(mat_h.at<uchar>(y, x));
					int qunantS = (int)UTIL::quantize(mat_s.at<uchar>(y, x));
					histogram[qunantH][qunantS]++;
					// Todo : ����ȭ�� h,s ���� ��� histogram�� ���� ���մϴ�. 

					/** your code here! **/

					// hint 1 : ����ȭ �� UTIL::quantize() �Լ��� �̿��ؼ� mat_h, mat_s�� ���� ����ȭ��ŵ�ϴ�. 
				}
			}

			// ������׷��� (hsv.rows * hsv.cols)���� ����ȭ�մϴ�. 
			for (int j = 0; j < 64; j++) {
				for (int i = 0; i < 64; i++) {
					histogram[j][i] = histogram[j][i] / hsv.rows*hsv.cols;

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

