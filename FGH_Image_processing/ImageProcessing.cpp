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

double ImageProcessing::colorCheckRGB(std::string input_filepath, int color_R, int color_G, int color_B){
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
	
	//答えとどれだけ離れているか
	score = pow(
		(color_avg[0] - color_B)*(color_avg[0] - color_B)
		+(color_avg[1] - color_G)*(color_avg[1] - color_G)
		+(color_avg[2] - color_R)*(color_avg[2] - color_R), 0.5);
	
	//距離を100点満点で表す
	score = (score/441.673 -1.0) * -100;
	//0の時表示がおかしくなるためそれを防ぐ（-9.97796e-008）
	if (score < 0.001 && score > -0.001)score = 0.0;


	cv::imshow("roi_img", roi_img);
	cv::imshow("平均色", color_img);
	cv::imshow("答え色", answer_img);

	return score;
}

double ImageProcessing::colorCheckHSV(std::string input_filepath, int color_R, int color_G, int color_B){
	double score = 0.0;
	int row, col;
	int roi[4]; //x,y,w,h
	cv::Mat roi_img_BGR, roi_img_HSV;
	cv::Mat src_img = cv::imread(input_filepath, 1);
	if (src_img.empty()) {
		std::cout << "file not found" << std::endl;
		return -1;
	}
	//cv::Mat src_img(cv::Size(200,200), CV_8UC3, cv::Scalar(0,0,0));
	cv::Mat color_img;
	cv::Mat answer_img_BGR(cv::Size(200, 200), CV_8UC3, cv::Scalar(color_B, color_G, color_R));
	cv::Mat answer_img_HSV;
	std::vector<cv::Mat> input_planes;
	std::vector<cv::Mat> answer_planes;
	int color_avg[3]; //H,S,V
	int answer_color[3]; //H,S,V

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
	//std::cout << "rows=" << src_img.rows << "cols" << src_img.cols << std::endl;
	roi_img_BGR = cv::Mat(src_img, cv::Rect(roi[0], roi[1], roi[2], roi[3]));

	cv::cvtColor(roi_img_BGR, roi_img_HSV, CV_BGR2HSV);
	

	cv::cvtColor(answer_img_BGR, answer_img_HSV, CV_RGB2HSV);
	//色の平均値を取得
	cv::split(roi_img_HSV, input_planes);
	cv::split(answer_img_HSV, answer_planes);
	for (int i = 0; i < 3; i++){
		cv::Mat m2, m3;
		cv::reduce(input_planes[i], m2, 0, CV_REDUCE_AVG);
		cv::reduce(m2, m3, 1, CV_REDUCE_AVG);
		color_avg[i] = m3.at<uchar>(0, 0);
		answer_color[i] = answer_planes[i].at<uchar>(0, 0);
		//std::cout << "avg " << color_avg[i] << std::endl;
		//std::cout << "ans " << answer_color[i] << std::endl;
	}
	//平均色画像作成
	color_img = cv::Mat(cv::Size(200, 200), CV_8UC3, cv::Scalar(color_avg[0], color_avg[1], color_avg[2]));
	//cv::cvtColor(color_img, color_img, CV_HSV2BGR);


	//答えとどれだけ離れているか

	double diff_H, diff_S, diff_V;
	diff_H = color_avg[0] - answer_color[0];
	diff_S = color_avg[1] - answer_color[1];
	diff_V = color_avg[2] - answer_color[2];
	if (diff_H > 90)diff_H = 90 - (diff_H -90); //近い方の距離（色相）
	score = pow(
		(diff_H)*(diff_H)
		+(diff_S)*(diff_S)
		+(diff_V)*(diff_V), 0.5
	);
	
	

	//距離を100点満点で表す
	score = (score / 371.685 - 1.0) * -100;
	//0の時表示がおかしくなるためそれを防ぐ（-9.97796e-008）
	if (score < 0.001 && score > -0.001)score = 0.0;
	//最高点がつかないので99より高いとで100点に
	if (score > 99 && score <= 100)score = 100;

/*	cv::imshow("BGRroi", roi_img_BGR);
	cv::imshow("HSVroi", roi_img_HSV);
	cv::imshow("平均色", color_img);
	cv::imshow("ansHSV", answer_img_HSV);
	cv::imshow("ansBGR", answer_img_BGR);
*/
	return score;
}

double ImageProcessing::imageMatching(std::string input_filepath, std::string answer_filepath){
	double score = 0;

	cv::Mat input_img = cv::imread(input_filepath);
	cv::Mat answer_img = cv::imread(answer_filepath);
	
	//ORB
	cv::Ptr<cv::FeatureDetector> detector_in = cv::ORB::create(80, 1.25f, 4, 7, 0, 2, 0, 31);
	cv::Ptr<cv::FeatureDetector> detector_an = cv::ORB::create(80, 1.25f, 4, 7, 0, 2, 0, 31);
	//cv::Ptr<cv::FeatureDetector> detector_in = cv::AKAZE::create();
	//cv::Ptr<cv::FeatureDetector> detector_an = cv::AKAZE::create();

	//特徴量抽出
	cv::Mat descriptors_in, descriptors_an;
	std::vector<cv::KeyPoint> keypoints_in, keypoints_an;
	detector_in->detect(input_img, keypoints_in);
	detector_an->detect(answer_img, keypoints_an);

	cv::Ptr<cv::DescriptorExtractor> extactor = cv::ORB::create(80, 1.25f, 4, 7, 0, 2, 0, 31);
	//cv::Ptr<cv::DescriptorExtractor> extactor = cv::AKAZE::create();
	extactor->compute(input_img, keypoints_in, descriptors_in);
	extactor->compute(input_img, keypoints_an, descriptors_an);

	//マッチング
	std::vector<cv::DMatch> matches;
	cv::BFMatcher macher(cv::NORM_HAMMING, true);
	macher.match(descriptors_in, descriptors_an, matches);

	
	//最小距離
	double min_dist = DBL_MAX;
	for (int i = 0; i < (int)matches.size(); i++){
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
	}
	if (min_dist < 1.0)min_dist = 1.0;

	//良いペアのみ残す
	const double threshold = 3.0 * min_dist;
	//const double threshold = 25.0;
	std::vector<cv::DMatch> matches_good;
	for (int i = 0; i < (int)matches.size(); i++){
		if (matches[i].distance < threshold){
			matches_good.push_back(matches[i]);
		}
	}
	
	//表示
	cv::Mat matchImage;
	cv::drawMatches(input_img, keypoints_in, answer_img, keypoints_an, matches_good, matchImage, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::DEFAULT);
	//cv::drawMatches(input_img, keypoints_in, answer_img, keypoints_an, matches, matchImage);
	cv::imshow("match", matchImage);
	cv::waitKey(0);

	/*cv::Mat input_img = cv::imread(input_filepath,1);
	cv::Mat answer_img = cv::imread(answer_filepath,1);


	if (input_img.empty()) {
		std::cout << "file not found" << std::endl;
		return -1;
	}
	cv::Mat gray_input,gray_answer;
	cv::cvtColor(input_img,gray_input, CV_BGR2GRAY);
	cv::normalize(gray_input, gray_input, 0, 255, cv::NORM_MINMAX);

	std::vector<cv::KeyPoint> keypoint;
	std::vector<cv::KeyPoint>::iterator itk;

	//ORB検出器に基づく特徴点抽出
	cv::Ptr<cv::ORB> detector = cv::ORB::create();
	detector->detect(gray_input, keypoint);
	//detector->compute(gray_input, keypoint,)
	cv::Scalar color(200, 250, 255);
	for (itk = keypoint.begin(); itk != keypoint.end(); ++itk){
		cv::circle(input_img, itk->pt, 1, color, -1);
		cv::circle(input_img, itk->pt, itk->size, color, 1, CV_AA);
	}
	
	cv::imshow("ORB", input_img);
	*/
	return score;
}


int ImageProcessing::countPeopleFaces(std::string input_filepath){
	int score;
	cv::Mat input_img = cv::imread(input_filepath);
	if (input_img.empty()) {
		std::cout << "file not found" << std::endl;
		return -1;
	}
	
	double scale = 1.0;
	cv::Mat gray, smallImg(cv::saturate_cast<int>(input_img.rows / scale), cv::saturate_cast<int>(input_img.cols / scale), CV_8UC1);
	cv::cvtColor(input_img, gray, CV_BGR2GRAY);
	cv::resize(gray, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
	cv::equalizeHist(smallImg, smallImg);

	std::string cascadeName = "../cascade/haarcascade_frontalface_default.xml";
	cv::CascadeClassifier face_cascade;
	if (!face_cascade.load(cascadeName)){
		std::cout << " Can't load cascade!" << std::endl;
		return -1;
	}

	std::vector<cv::Rect> faces;

	face_cascade.detectMultiScale(smallImg, faces, 1.1, 2,
		CV_HAAR_SCALE_IMAGE,
		cv::Size(10, 10));

	std::vector<cv::Rect>::const_iterator r = faces.begin();
	for (; r != faces.end(); ++r){
		cv::Point center;
		int radious;
		center.x = cv::saturate_cast<int>((r->x + r->width*0.5)*scale);
		center.y = cv::saturate_cast<int>((r->y + r->height*0.5)*scale);
		radious = cv::saturate_cast<int>((r->width + r->height)*0.25*scale);
		cv::circle(input_img, center, radious, cv::Scalar(80, 80, 255), 3, 8, 0);
	}
	
	score = faces.size();

	cv::imshow("result", input_img);
	return score;
}
 