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
	if (src_img.empty()) {
		std::cout << "file not found" << std::endl;
		return -1;
	}
	//cv::Mat src_img(cv::Size(200,200), CV_8UC3, cv::Scalar(0,0,0));
	cv::Mat color_img;
	cv::Mat answer_img(cv::Size(200, 200), CV_8UC3, cv::Scalar(color_B, color_G, color_R));
	std::vector<cv::Mat> planes;
	int color_avg[3]; //B,G,R


	//�摜�̒��S������؂蔲��
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

	//�F�̕��ϒl���擾
	cv::split(roi_img, planes);
	for (int i = 0; i < 3; i++){
		cv::Mat m2, m3;
		cv::reduce(planes[i], m2, 0, CV_REDUCE_AVG);
		cv::reduce(m2, m3, 1, CV_REDUCE_AVG);
		color_avg[i] = m3.at<uchar>(0, 0);
	}
	
	//���ϐF�摜�쐬
	color_img = cv::Mat(cv::Size(200, 200), CV_8UC3, cv::Scalar(color_avg[0], color_avg[1], color_avg[2]));
	
	cv::imshow("���ϐF",color_img);
	cv::imshow("�����F", answer_img);

	//�����Ƃǂꂾ������Ă��邩
	score = pow(
		(color_avg[0] - color_B)*(color_avg[0] - color_B)
		+(color_avg[1] - color_G)*(color_avg[1] - color_G)
		+(color_avg[2] - color_R)*(color_avg[2] - color_R), 0.5);
	
	//������100�_���_�ŕ\��
	score = (score/441.673 -1.0) * -100;
	//0�̎��\�������������Ȃ邽�߂����h���i-9.97796e-008�j
	if (score < 0.001 && score > -0.001)score = 0.0;

	return score;
}

double ImageProcessing::imageMatching(std::string input_filepath, std::string answer_filepath){
	double score;
	cv::Mat input_img = cv::imread(input_filepath,1);
	if (input_img.empty()) {
		std::cout << "file not found" << std::endl;
		return -1;
	}
	cv::Mat gray_input,gray_answer;
	cv::cvtColor(input_img,gray_input, CV_BGR2GRAY);
	cv::normalize(gray_input, gray_input, 0, 255, cv::NORM_MINMAX);

	std::vector<cv::KeyPoint> keypoint;
	std::vector<cv::KeyPoint>::iterator itk;

	//ORB���o��Ɋ�Â������_���o
	cv::Ptr<cv::ORB> detector = cv::ORB::create();
	detector->detect(gray_input, keypoint);
	//detector->compute(gray_input, keypoint,)
	cv::Scalar color(200, 250, 255);
	for (itk = keypoint.begin(); itk != keypoint.end(); ++itk){
		cv::circle(input_img, itk->pt, 1, color, -1);
		cv::circle(input_img, itk->pt, itk->size, color, 1, CV_AA);
	}
	
	cv::imshow("ORB", input_img);

	return score;
}
 