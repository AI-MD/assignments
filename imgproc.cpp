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
}

