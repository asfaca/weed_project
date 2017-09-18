#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace cv;
using namespace std;

/*
sensitivity is for detect yellow-like-green or blue-like-green.
if sensitivity is low, it can detect yellow-like-green or blue-like-green,
but the accuracy of green detection is low.
default is 50.
brightness is the degree of bright of green pixel. Domain of brightness is 0 - 255.
If brightness is high, this module can detect bright green but not dark green.
*/
class ProcessImage {
public:
	ProcessImage(String imagaName);
	Mat getLeafImage(int brightness, int sensitivity);

private:
	Mat image;
	double greenRatio = 0;
	double rgbSum = 0;
	int count = 0;
	int yellowSensitity = 0;
	int blueSensitity = 0;
	int sensitivity = 0;
	int brightness = 0;
};

ProcessImage::ProcessImage(String imagaName) {
	this->image = imread(imagaName, IMREAD_COLOR);
}
Mat ProcessImage::getLeafImage(int brightness, int sensitivity) {
	this->brightness = brightness;
	this->sensitivity = sensitivity;

	for (int i = 0; i < image.rows; i++) {
		for (int k = 0; k < image.cols * 3; k += 3) {
			if (image.at<uchar>(i, k + 1) > image.at<uchar>(i, k) + sensitivity && image.at<uchar>(i, k + 1) > image.at<uchar>(i, k + 2) + sensitivity && image.at<uchar>(i, k + 1) > brightness) {
				rgbSum += (double)image.at<uchar>(i, k + 1) / (double)(image.at<uchar>(i, k) + image.at<uchar>(i, k + 1) + image.at<uchar>(i, k + 2));
				count++;
			}
		}
	}

	greenRatio = (rgbSum / (double)count) - (rgbSum / ((double)count) * 0.08); //0.08 is for error.

	cout << greenRatio;


	for (int i = 0; i < image.rows; i++) {
		for (int k = 0; k < image.cols * 3; k += 3) {
			rgbSum = (double)image.at<uchar>(i, k + 1) / (double)(image.at<uchar>(i, k) + image.at<uchar>(i, k + 1) + image.at<uchar>(i, k + 2));

			if (rgbSum < greenRatio) {
				image.at<uchar>(i, k) = 0;
				image.at<uchar>(i, k + 1) = 0;
				image.at<uchar>(i, k + 2) = 0;
			}
			else {
				image.at<uchar>(i, k) = 0;
				image.at<uchar>(i, k + 1) = 255;
				image.at<uchar>(i, k + 2) = 0;
			}
		}
	}
	greenRatio = 0;
	rgbSum = 0;
	count = 0;

	return image;
}


int main(int argc, char** argv)
{
	ProcessImage opencv("leaf7.jpg");
	Mat image = opencv.getLeafImage(50, 20);


	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);


	waitKey(0);

	return 0;
}