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
	//�w�肵���F�Ɖ摜�i�̒��S���Ӂj�̐F���ǂꂾ���߂���
	double colorCheck(std::string input_filepath, int color_B, int color_G, int color_R);
	//�����_�ɂ��}�b�`���O(ORB)
	double imageMatching(std::string input_filepath, std::string answer_filepath);
};

