r/
// Created by Nicky Valdecanas on 2/1/19.
//
#include "../Lab02/EasyBMP.h"


int main(){
    BMP deer;
    BMP deerOut;
    deer.ReadFromFile("sierpinski.bmp");
    int h = deer.TellHeight();
    int w = deer.TellWidth();
    std::cout <<  deer.TellHeight() << " ";
    std::cout << deer.TellWidth();
    deerOut.SetSize(w,h);
    for (int i = 0; i < w +1; i++) {
        for (int j = 0; j < h +1; j++) {
            deerOut(i,j)->Red = (deer(2*i, 2*j)->Red + deer(2*i+1, 2*j)->Red + deer(2*i, 2*j+1)->Red + deer(2*i+1, 2*j+1)->Red)/4;

            deerOut(i, j)->Green = (deer(2*i, 2*j)->Green + deer(2*i+1, 2*j)->Green + deer(2*i, 2*j+1)->Green + deer(2*i+1, 2*j+1)->Green)/4;

            deerOut(i, j)->Blue = (deer(2*i, 2*j)->Blue + deer(2*i+1, 2*j)->Blue + deer(2*i, 2*j+1)->Blue + deer(2*i+1, 2*j+1)->Blue)/4;

        }
    }
    deerOut.WriteToFile("out.bmp");
    /*BMP sierpinski;

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
