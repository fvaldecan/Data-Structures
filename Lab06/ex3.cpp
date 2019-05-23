#include "EasyBMP.h"
void scale(BMP &input, BMP &output);
void draw(BMP &input, BMP &output);
int main(){
    BMP einsteinIn;
    BMP einsteinOut;

    einsteinIn.ReadFromFile("sierpinski.bmp");
    int height = einsteinIn.TellHeight();
    int width = einsteinIn.TellWidth();

    einsteinOut.SetSize(einsteinIn.TellWidth(), einsteinIn.TellHeight());
    Rescale(einsteinIn, 'f', 512);

    einsteinOut.SetSize(width, height);
    draw(einsteinIn, einsteinOut);



    einsteinOut.WriteToFile("out.bmp");
}
void scale(BMP &input, BMP &output){
    int height = input.TellHeight() /2;
    int width = input.TellWidth() / 2;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            output(i,j)->Red = (input(2*i, 2*j)->Red + input(2*i+1, 2*j)->Red + input(2*i, 2*j+1)->Red + input(2*i+1, 2*j+1)->Red)/4;
            output(i,j)->Blue = (input(2*i, 2*j)->Green + input(2*i+1, 2*j)->Green + input(2*i, 2*j+1)->Green + input(2*i+1, 2*j+1)->Green)/4;
            output(i,j)->Green = (input(2*i, 2*j)->Blue + input(2*i+1, 2*j)->Blue + input(2*i, 2*j+1)->Blue + input(2*i+1, 2*j+1)->Blue)/4;
        }
    }
}
void draw(BMP &input, BMP &output) {
    BMP temp;
    int width = input.TellWidth();
    int height = input.TellHeight();
    if (width == 1 && height == 1) {
        RangedPixelToPixelCopy(input, 0, width, height, 0, output, 0, output.TellWidth() - 1);
        return;
    } else {
        BMP temp;
        temp.SetSize(input.TellWidth() / 2, input.TellHeight() / 2);
        scale(input, temp);
        RangedPixelToPixelCopy(input, 0, width, height, 0, output, 0, output.TellWidth() / 2);
        BMP temp2;
        temp2.SetSize(temp.TellWidth() *2, temp.TellHeight());
        draw(temp, temp2);
        //RangedPixelToPixelCopy(temp2, 0, temp2.TellWidth(), temp2.TellHeight(), 0, output, output.TellHeight() / 2, 0);
        //RangedPixelToPixelCopy(temp2, 0, temp2.TellWidth()/2, temp2.TellHeight(), 0, output, 0, 0);
        //RangedPixelToPixelCopy(temp2, 0, temp2.TellWidth()/2, temp2.TellHeight(), 0, output, output.TellWidth()/4, 0);
        //RangedPixelToPixelCopy(temp2, 0, temp2.TellWidth(), temp2.TellHeight()/2, 0, output, output.TellWidth()/2, output.TellHeight()/2);
        //RangedPixelToPixelCopy(temp2, 0, temp2.TellWidth(), temp2.TellHeight()/2, 0, output, output.TellWidth()/2, output.TellHeight() * 0.75);
    }
}