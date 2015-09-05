#include "ImageProcessing.hpp"

int main(){
	
	ImageProcessing IP;

	IP.showImage("../image/lenna.png");
	std::cout << "score " << IP.colorCheckRGB("../image/lenna.png", 100, 100, 200) << std::endl;
	IP.imageMatching("../image/lenna_rotated.png", "../image/lenna.png");
	cv::waitKey(0);
	
	
	return 0;
}

