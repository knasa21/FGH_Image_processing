#include "ImageProcessing.hpp"

int main(){
	
	ImageProcessing IP;
	int R, G, B;
	std::string filename;

	std::cin >> filename;
	/*std::cin >> R;
	std::cin >> G;
	std::cin >> B;*/
	

	//IP.showImage("../image/lenna.png");
	//std::cout << "score " << IP.colorCheckRGB("../image/lenna.png", 100, 100, 255) << std::endl;
	//std::cout << "score " << IP.colorCheckHSV("../image/lenna.png", 100, 100, 255) << std::endl;
	
	//std::cout << IP.colorCheckHSV(filename, R, G, B) << std::endl;
	//IP.imageMatching("../image/hokousya.png", "../image/hyousikis.png");
	std::cout << IP.countPeopleFaces(filename) << std::endl;
	//cv::waitKey(0);
	
	
	return 0;
}

