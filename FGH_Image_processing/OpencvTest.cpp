#include "ImageProcessing.hpp"

int main(){
	
	ImageProcessing IP;

	IP.showImage("../image/lenna.png");
	std::cout << "score " << IP.colorCheckRGB("../image/lenna.png", 0, 0, 255) << std::endl;
	std::cout << "score " << IP.colorCheckHSV("../image/lenna.png", 0, 0, 255) << std::endl;
	//IP.imageMatching("../image/lenna_rotated.png", "../image/lenna.png");
	cv::waitKey(0);
	
	
	return 0;
}

