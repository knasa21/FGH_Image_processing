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
	//画像の表示
	void showImage(std::string filepath);
	//指定した色と画像（の中心周辺）の色がどれだけ近いか
	double colorCheck(std::string input_filepath, int color_B, int color_G, int color_R);
	//特徴点によるマッチング(ORB)
	double imageMatching(std::string input_filepath, std::string answer_filepath);
};

