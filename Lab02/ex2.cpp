//
// Created by Nicky Valdecanas on 2/1/19.
//
#include "../Lab02/EasyBMP.h"


int main(){

    BMP sierpinski;

    sierpinski.SetSize(256, 256);
    int xyz[3][2] = {{128,5},{5,251},{251,251}}; //Create array of vertcies points
    int startPoint[1][2] = {{171,34}}; // P(0)

    for (int i = 0; i < 10000; i++)
    {

        //(x1, y1)
        int randomPoint = rand() % 3;
        int x1 = (xyz[randomPoint][0] + startPoint[0][0]) / 2;
        int y1 = (xyz[randomPoint][1] + startPoint[0][1]) / 2;

        //New start point
        startPoint[0][0] = x1; //New x1
        startPoint[0][1] = y1; //New y1

        sierpinski(x1,y1)->Red = 255;
        sierpinski(x1,y1)->Blue = 0;
        sierpinski(x1,y1)->Green = 0;
    }
    sierpinski.WriteToFile("sierpinski.bmp");*/
    return 0;
}
