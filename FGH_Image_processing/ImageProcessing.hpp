#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
class ImageProcessing
{
public:
	ImageProcessing();
	~ImageProcessing();
	//�摜�̕\��
	void showImage(std::string filepath);
	//�w�肵���F�Ɖ摜�i�̒��S���Ӂj�̐F���ǂꂾ���߂���
	double colorCheck(std::string input_filepath, int color_B, int color_G, int color_R);
};

