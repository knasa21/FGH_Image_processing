#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
class ImageProcessing
{
public:
	ImageProcessing();
	~ImageProcessing();
	//�摜�̕\��
	void showImage(std::string filepath);
	//RGB�w�肵���F�Ɖ摜�i�̒��S���Ӂj�̐F���ǂꂾ���߂���
	double colorCheckRGB(std::string input_filepath, int color_R, int color_G, int color_B);
	//HSV�w�肵���F�Ɖ摜�i�̒��S���Ӂj�̐F���ǂꂾ���߂���
	double colorCheckHSV(std::string input_filepath, int color_R, int color_G, int color_B);
	//�����_�ɂ��}�b�`���O(ORB)
	double imageMatching(std::string input_filepath, std::string answer_filepath);
};

