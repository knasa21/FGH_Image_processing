#include "ImageProcessing.hpp"


ImageProcessing::ImageProcessing()
{
}


ImageProcessing::~ImageProcessing()
{
}

void ImageProcessing::showImage(std::string filepath)
{
	cv::Mat src_img = cv::imread(filepath, 1);
	if (src_img.empty()) {
		std::cout << "file not found" << std::endl;
		return;
	}
	//cv::namedWindow("src_img",CV_WINDOW_AUTOSIZE);
	cv::imshow("src_img", src_img);
}

double ImageProcessing::colorCheck(std::string input_filepath, int color_B, int color_G, int color_R){
	double score = 0.0;
	int row, col;
	int roi[4]; //x,y,w,h
	cv::Mat roi_img;
	cv::Mat src_img = cv::imread(input_filepath, 1);
	//cv::Mat src_img(cv::Size(200,200), CV_8UC3, cv::Scalar(0,0,0));
	cv::Mat color_img;
	cv::Mat answer_img(cv::Size(200, 200), CV_8UC3, cv::Scalar(color_B, color_G, color_R));
	std::vector<cv::Mat> planes;
	int color_avg[3]; //B,G,R


	if (src_img.empty()) {
		std::cout << "file not found" << std::endl;
		return 0;
	}

	//画像の中心部分を切り抜き
	row = src_img.rows;
	col = src_img.cols;
	if (col > 100){
		roi[0] = col / 2 - 50;
		roi[2] = 100;
	}
	else{
		roi[0] = 0;
		roi[2] = col;
	}

	if (row > 100){
		roi[1] = row / 2 - 50;
		roi[3] = 100;
	}
	else{
		roi[1] = 0;
		roi[3] = row;
	}
	std::cout << "rows=" << src_img.rows << "cols" << src_img.cols << std::endl;
	roi_img = cv::Mat(src_img, cv::Rect(roi[0],roi[1],roi[2],roi[3]));
	imshow("roi_img", roi_img);

	//色の平均値を取得
	cv::split(roi_img, planes);
	for (int i = 0; i < 3; i++){
		cv::Mat m2, m3;
		cv::reduce(planes[i], m2, 0, CV_REDUCE_AVG);
		cv::reduce(m2, m3, 1, CV_REDUCE_AVG);
		color_avg[i] = m3.at<uchar>(0, 0);
	}
	
	//平均色画像作成
	color_img = cv::Mat(cv::Size(200, 200), CV_8UC3, cv::Scalar(color_avg[0], color_avg[1], color_avg[2]));
	
	cv::imshow("平均色",color_img);
	cv::imshow("答え色", answer_img);

	//答えとどれだけ離れているか
	score = pow(
		(color_avg[0] - color_B)*(color_avg[0] - color_B)
		+(color_avg[1] - color_G)*(color_avg[1] - color_G)
		+(color_avg[2] - color_R)*(color_avg[2] - color_R), 0.5);
	
	//距離を100点満点で表す
	score = (score/441.673 -1.0) * -100;
	//0の時表示がおかしくなるためそれを防ぐ（-9.97796e-008）
	if (score < 0.001 && score > -0.001)score = 0.0;

	return score;
}
 