#include "EasyBMP.h"


void draw(BMP & input, BMP & output);

int main() {

    BMP input;
    input.ReadFromFile("mid1_opem_image.bmp");

    int width = input.TellWidth();
    int height = input.TellHeight();
    BMP output;
    output.SetSize(width, height);
    output.SetBitDepth(24);
    Rescale(input, 'p', 50);
    RangedPixelToPixelCopy(input, 0, output.TellWidth() /2, output.TellHeight() /2, 0, output, 0, output.TellHeight() / 2);
    draw(input,output);

    output.WriteToFile("output.bmp");
    return 0;

}

void draw(BMP & input, BMP & output)
{
    int width = input.TellWidth();
    int height = input.TellHeight();

    BMP temp;
    temp.SetSize(width, height);
    temp.SetBitDepth(24);
    Rescale(input, 'p', 50);
    RangedPixelToPixelCopy(input, 0, width / 2, height / 2, 0, temp, 0, height / 2);
    if (input.TellWidth() == 1 || input.TellHeight() == 1) {
        RangedPixelToPixelCopy(input, 0, output.TellWidth() / 2, output.TellHeight() / 2, 0, output, output.TellWidth() /2, output.TellHeight()/4);
        RangedPixelToPixelCopy(input, 0, output.TellWidth() / 2, output.TellHeight() / 2, 0, output, output.TellWidth() /2, 0);
        RangedPixelToPixelCopy(input, 0, output.TellWidth() / 2, output.TellHeight() / 2, 0, output, 0, 0);
        return;
    }
    RangedPixelToPixelCopy(temp, 0, output.TellWidth() / 2, output.TellHeight() / 2, 0, output, output.TellWidth() /2, output.TellHeight()/4);
    draw(input, temp);
    RangedPixelToPixelCopy(temp, 0, output.TellWidth() / 2, output.TellHeight() / 2, 0, output, output.TellWidth() /2, 0);
    RangedPixelToPixelCopy(temp, 0, output.TellWidth() / 2, output.TellHeight() / 2, 0, output, 0, 0);
}

