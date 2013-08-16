#ifndef KALMAN__H
#define KALMAN__H

#include <iostream>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>

using namespace cv;

//#define fodao

#ifdef fodao
class atsKalman {
	public:
		atsKalman() {
			KalmanFilter KF(6, 2, 0);
			Mat_<float> state(4, 1); /* (x, y, Vx, Vy)*/
			Mat processNoise(6, 1, CV_32F);
			Mat_<float> measurement(2, 1);
			measurement.setTo(Scalar(0));

			KFs = KF;
			measurements = measurement;
		}
		void setKalman(int x, int y) {
			/*KFs.statePre.at<float>(0) = x;
			 KFs.statePre.at<float>(1) = y;
			 KFs.statePre.at<float>(2) = 0;
			 KFs.statePre.at<float>(3) = 0;
			 KFs.transitionMatrix = *(Mat_<float>(4, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);*/
			KFs.statePre.at<float>(0) = x;
			KFs.statePre.at<float>(1) = y;
			KFs.statePre.at<float>(2) = 0;
			KFs.statePre.at<float>(3) = 0;
			KFs.statePre.at<float>(4) = 0;
			KFs.statePre.at<float>(5) = 0;
			KFs.transitionMatrix = *(Mat_<float>(6, 6) << 1, 0, 1, 0, 0.5, 0, 0, 1, 0, 1, 0, 0.5, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1);
			KFs.measurementMatrix = *(Mat_<float>(2, 6) << 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0);

			setIdentity(KFs.measurementMatrix);
			setIdentity(KFs.processNoiseCov, Scalar::all(1e-4));
			setIdentity(KFs.measurementNoiseCov, Scalar::all(1e-1));
			setIdentity(KFs.errorCovPost, Scalar::all(.1));

		}
		Point step1(float & x, float & y) {
			Mat prediction = KFs.predict();
			Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

			x = (float) predictPt.x;
			y = (float) predictPt.y;
			std::cout << predictPt.x << " " << predictPt.y << std::endl;
			return predictPt;
		}
		Point step2(float & x, float & y) {
			Mat estimated = KFs.correct(measurements);
			Point statePt(estimated.at<float>(0), estimated.at<float>(1));

			x = (float) statePt.x;
			y = (float) statePt.y;
			std::cout << statePt.x << " " << statePt.y << " " << estimated.at<float>(2) << " " << estimated.at<float>(3) << std::endl;
			return statePt;
		}
		void changeMeasure(float x, float y) {
			measurements(0) = x;
			measurements(1) = y;

			std::cout << measurements(0) << " " << measurements(1) << std::endl;
		}
	private:
		KalmanFilter KFs;
		Mat_<float> measurements;
};
#endif

#define fodao2
#ifdef fodao2

class Kalman {
	public:
		Kalman() {
			KalmanFilter KF(6, 2, 0);
			Mat_<float> state(4, 1); /* (x, y, Vx, Vy)*/
			Mat processNoise(6, 1, CV_32F);
			Mat_<float> measurement(2, 1);
			measurement.setTo(Scalar(0));

			KFs = KF;
			measurements = measurement;
		}
		void setKalman(int x, int y) {
			/*KFs.statePre.at<float>(0) = x;
			 KFs.statePre.at<float>(1) = y;
			 KFs.statePre.at<float>(2) = 0;
			 KFs.statePre.at<float>(3) = 0;
			 KFs.transitionMatrix = *(Mat_<float>(4, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);*/
			KFs.statePre.at<float>(0) = x;
			KFs.statePre.at<float>(1) = y;
			KFs.statePre.at<float>(2) = 0;
			KFs.statePre.at<float>(3) = 0;
			KFs.statePre.at<float>(4) = 0;
			KFs.statePre.at<float>(5) = 0;
			KFs.transitionMatrix = *(Mat_<float>(6, 6) << 1, 0, 10, 0, 0, 0, 0, 1, 0, 10, 0, 0, 0, 0, 1, 0, 5, 0, 0, 0, 0, 1, 0, 5, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1);
			KFs.measurementMatrix = *(Mat_<float>(2, 6) << 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0);

			setIdentity(KFs.measurementMatrix);
			setIdentity(KFs.processNoiseCov, Scalar::all(1e-4));
			setIdentity(KFs.measurementNoiseCov, Scalar::all(1e-1));
			setIdentity(KFs.errorCovPost, Scalar::all(.1));

		}
		Point step1(float & x, float & y) {
			Mat prediction = KFs.predict();
			Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

			x = (float) predictPt.x;
			y = (float) predictPt.y;
			return predictPt;
		}
		Point step2(float & x, float & y) {
			Mat estimated = KFs.correct(measurements);
			Point statePt(estimated.at<float>(0), estimated.at<float>(1));

			x = (float) statePt.x;
			y = (float) statePt.y;
			return statePt;
		}
		void changeMeasure(float x, float y) {
			measurements(0) = x;
			measurements(1) = y;

		}
	private:
		KalmanFilter KFs;
		Mat_<float> measurements;
};

#else

class atsKalman {
	public:
	atsKalman() {
		KalmanFilter KF(4, 2, 0);
		Mat_<float> state(4, 1); /* (x, y, Vx, Vy)*/
		Mat processNoise(4, 1, CV_32F);
		Mat_<float> measurement(2, 1);
		measurement.setTo(Scalar(0));

		KFs = KF;
		measurements = measurement;
	}
	void setKalman(int x, int y) {
		KFs.statePre.at<float>(0) = x;
		KFs.statePre.at<float>(1) = y;
		KFs.statePre.at<float>(2) = 0;
		KFs.statePre.at<float>(3) = 0;
		KFs.transitionMatrix = *(Mat_<float>(4, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

		setIdentity(KFs.measurementMatrix);
		setIdentity(KFs.processNoiseCov, Scalar::all(1e-4));
		setIdentity(KFs.measurementNoiseCov, Scalar::all(1e-1));
		setIdentity(KFs.errorCovPost, Scalar::all(.1));

	}
	Point step1(float & x, float & y) {
		Mat prediction = KFs.predict();
		Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

		x = (float) predictPt.x;
		y = (float) predictPt.y;
		std::cout << predictPt.x << " " << predictPt.y << std::endl;
		return predictPt;
	}
	Point step2(float & x, float & y) {
		Mat estimated = KFs.correct(measurements);
		Point statePt(estimated.at<float>(0), estimated.at<float>(1));

		x = (float) statePt.x;
		y = (float) statePt.y;
		std::cout << statePt.x << " " << statePt.y << " " << estimated.at<float>(2) << " " << estimated.at<float>(3) << std::endl;
		return statePt;
	}
	void changeMeasure(int x, int y) {
		measurements(0) = x;
		measurements(1) = y;

		std::cout << measurements(0) << " " << measurements(1) << std::endl;
	}
	private:
	KalmanFilter KFs;
	Mat_<float> measurements;
};
#endif

#endif
