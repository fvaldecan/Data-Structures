#include "EasyBMP.h"
#include <iostream>
void rescale(BMP &inImage, BMP &outImage);
void RecurseCopy(BMP &inImage, BMP &outImage);
int main(int argc, char** argv){
    const char* inputfile;
    const char* outputfile;
    BMP deerIn;
    BMP deerOut;

    if (argc > 1) {
        inputfile = argv[1];
    }
    else inputfile = "input.bmp";

    if (argc > 2) outputfile = argv[2];
    else outputfile = "ex3output.bmp";

    deerIn.ReadFromFile(inputfile);
    int height = deerIn.TellHeight();
    int width = deerIn.TellWidth();


    deerOut.SetSize(width, height);
    RecurseCopy(deerIn, deerOut);



    deerOut.WriteToFile(outputfile);
}
void rescale(BMP &inImage, BMP &outImage){
    int height = inImage.TellHeight();
    int width = inImage.TellWidth() /2;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            outImage(i,j)->Red = (inImage(2*i, j)->Red + inImage(2*i +1, j)->Red) /2;
            outImage(i,j)->Blue = (inImage(2*i, j)->Blue + inImage(2*i +1, j)->Blue) /2;
            outImage(i,j)->Green = (inImage(2*i, j)->Green + inImage(2*i +1, j)->Green) /2;
        }
    }
}
void RecurseCopy(BMP &inImage, BMP &outImage) {

    int width = inImage.TellWidth();
    int height = inImage.TellHeight();
    if (height == 2 or width == 1) {
        RangedPixelToPixelCopy(inImage, 0, width, height, 0, outImage, 0, outImage.TellWidth());
        return;
    }
    BMP temp;
    temp.SetSize(width / 2, height);
    rescale(inImage, temp);
    RangedPixelToPixelCopy(temp, 0, width, height, 0, outImage, 0, 0);
    BMP temp1;
    temp1.SetSize(width /2, height /2);
    Rescale(inImage, 'p', 50);
    RangedPixelToPixelCopy(inImage, 0, inImage.TellWidth(), inImage.TellHeight(), 0, temp1, 0, 0);
    BMP temp2;
    temp2.SetSize(width / 2, height / 2);
    RecurseCopy(temp1, temp2);
    RangedPixelToPixelCopy(temp2, 0, temp2.TellWidth(), temp2.TellHeight(), 0, outImage, outImage.TellWidth() / 2, 0);
    RangedPixelToPixelCopy(temp2, 0, temp2.TellWidth(), temp2.TellHeight(), 0, outImage, outImage.TellWidth() / 2, outImage.TellHeight() /2);



}

