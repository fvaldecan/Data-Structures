#include "EasyBMP.h"

int main() {
	BMP checkerboard;
	checkerboard.SetSize(128, 128);
	checkerboard.SetBitDepth(8);
	for (int i = 0; i < 128; i++){
	    for (int j = 0; j < 128; j++){
            int rowNo = i / 16;
            int colNo = j / 16;
	        if ((rowNo + colNo) % 2 == 0){ // row + col = even
	            checkerboard(i,j)->Red = 255;
                checkerboard(i,j)->Blue = 0;
                checkerboard(i,j)->Green = 0;
	        } else {
                checkerboard(i,j)->Red = 0;
                checkerboard(i,j)->Blue = 0;
                checkerboard(i,j)->Green = 0;
	        }

	    }
	}

	checkerboard.WriteToFile("board.bmp");
	return 0;
}

