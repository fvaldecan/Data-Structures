//
// Created by Nicky Valdecanas on 1/31/19.
//

#include "EasyBMP.h"
#include <iostream>
using namespace std;

void colorToGray(BMP & Output) {
    int picWidth = Output.TellWidth();
    int picHeight =Output.TellHeight();
    Output.SetBitDepth(1); //compression happens here
    for (int i = 0; i < picWidth-1; ++i)
        for (int j = 0; j < picHeight-1; ++j) {
            int col = 0.1* Output(i, j)->Blue +
                      0.6*Output(i,j)->Green +0.3* Output(i,j)->Red; if (col > 127) {
                Output(i,j)->Red = 255;
                Output(i,j)->Blue = 255;
                Output(i,j)->Green = 255;
            }
        }
}
int main( int argc, char* argv[])
{
    BMP myImage;
    myImage.ReadFromFile(argv[1]);
    colorToGray(myImage);
    myImage.WriteToFile(argv[2]);
    return 0;

