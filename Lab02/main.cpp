#include <iostream>
#include "EasyBMP.h"

int main(int argc, char * argv[]){
	BMP inImg;
	inImg.ReadFromFile(argv[1]);
	std::cout<< "Width " << inImg.TellWidth() << " pixels" << std::endl;
	std::cout << "Height " << inImg.TellHeight() <<" pixels" << std::endl;
	return 0;
}
