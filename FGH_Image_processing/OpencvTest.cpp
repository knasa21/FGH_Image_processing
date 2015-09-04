#include "ImageProcessing.hpp"

int main(){
	
	ImageProcessing IP;

	IP.showImage("../image/lenna.png");
	std::cout << "score " << IP.colorCheck("../image/lenna.png", 100, 100, 200) << std::endl;
	IP.imageMatching("../image/lenna.png", "../image/lenna.png");
	cv::waitKey(0);
	
	
	return 0;
}

