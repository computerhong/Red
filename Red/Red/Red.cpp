// Red.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
	cv::Mat image = cv::imread("E:\\Images\\Lena.jpg", -1);
	cv::imshow("Lena", image);
	cv::waitKey(0);
	return 0;
}

