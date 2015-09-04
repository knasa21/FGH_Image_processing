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
	//画像の表示
	void showImage(std::string filepath);
	//指定した色と画像（の中心周辺）の色がどれだけ近いか
	double colorCheck(std::string input_filepath, int color_B, int color_G, int color_R);
};

