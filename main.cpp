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
	String imageName = "Lenna.png";
	String grayImageName = "gray.bmp";

	Mat image;
	image = imread(imageName, IMREAD_COLOR);


	for (int i = 0; i < image.rows; i++) {
		for (int k = 0; k < image.cols * 3; k++) {
			image.at<uchar>(i, k) /= 3;
			//cout << (int)image.at<uchar>(i, k) << ", ";
		}
		//cout << endl;
	}
	
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);
	

	waitKey(0);

	return 0;
}