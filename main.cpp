#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	String imageName = "leaf2.jpg";
	double greenRatio = 0;
	double rgbSum = 0;
	int count = 0;

	Mat image;
	image = imread(imageName, IMREAD_COLOR);

	/*
	1. find avg greean ratio among G > R,B.
	2. make black and green using green ratio.
	*/
	
	for (int i = 0; i < image.rows; i++) {
		for (int k = 0; k < image.cols * 3; k+=3) {
			if (image.at<uchar>(i, k + 1) > image.at<uchar>(i, k) && image.at<uchar>(i, k + 1) > image.at<uchar>(i, k + 2)) {
				rgbSum += (double)image.at<uchar>(i, k + 1) / (double)(image.at<uchar>(i, k) + image.at<uchar>(i, k + 1) + image.at<uchar>(i, k + 2));
				count++;
			}
		}
	}

	greenRatio = rgbSum / (double)count;

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

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);


	waitKey(0);

	return 0;
}