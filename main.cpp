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
	String imageName = "newimg.png";
	String grayImageName = "gray.bmp";

	Mat image;
	image = imread(imageName, IMREAD_COLOR); 

	uchar *pixel = (uchar*)image.data;

	
	cout << image.cols << " and " << image.rows;

	for (int i = 0; i < image.rows; i++) {
		for (int k = 0; k < image.cols; k++) {
			//out << (int)pixel[i + k] << endl;
			//cout << (int)pixel[i + k]/2 << endl;
		}
	}


	waitKey(0);

	return 0;
}