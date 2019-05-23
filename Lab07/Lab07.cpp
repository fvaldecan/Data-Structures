/* Name: Franco Dominic Valdecanas
 * Date: March 23, 2019
 * Program: Lab07.cpp
 * Description:
 * The goal of this program is to take an image, turn each letter
 * from black to green, and box them in red. It will also output
 * the number of lines and characters the image has.
 */
#include <iostream>
#include "EasyBMP.h"
using namespace std;
const int MSIZE = 10000;

// point class is used by queue class
class point{
private:
    int x; int y;

public:
    point(int p, int q){
        x = p; y = q;
    }

    int getx(){
        return x;
    }

    int gety() {
        return y;
    }

};

class queue {

private:
    point* Q[MSIZE];
    int front, rear, size;

public:
    queue() {
        // initialize an empty queue
        front = 0; rear = 0; size = 0;
        for (int j=0; j < MSIZE; ++j)
            Q[j] = 0;
    }

    void insert(int n,int m){
        point* temp = new point(n,m);
        insert(temp);
    }

    void insert(point* x) { //Insert point in queue
        if (size != MSIZE) {
            front++; size++;
            if (front == MSIZE) front = 0;
            Q[front] = x;
        }
    }

    point del() { // Delete point in queue
        if (size != 0) {
            rear++; if (rear == MSIZE) rear = 0;
            point temp(Q[rear]->getx(), Q[rear]->gety());
            size--;
            return temp;
        }
        else return point(-1,-1);
    }

    void print() { //Print Contents of Queue
        for (int j = 1; j <= size; ++j) {
            int i = front - j + 1;
            cout << "x = " << Q[i]->getx() << " y = "
                 << Q[i]->gety() << endl;
        }
        cout << "-----------------------" << endl;
    }

    bool isEmpty() {
        return (size == 0);
    }
};
void colorToGray(BMP & Output);
void label(BMP &inImage, BMP &outImage);
bool isValid(int i, int j, int width, int height);
void drawH(int x1, int x2, int y, BMP &outImage);
void drawV(int y1, int y2, int x, BMP & outImage);
int main(int argc, char** argv){
    const char *inputfile;
    const char *outputfile;

    // Intialize BMP input and output images
    BMP inImage;
    BMP outImage;

    if (argc > 1) {
        inputfile = argv[1];
    } else inputfile = "in.bmp";

    if (argc > 2) outputfile = argv[2];
    else outputfile = "out.bmp";

    inImage.ReadFromFile(inputfile); // Read in image file
    inImage.SetBitDepth(24); // Set Bit Depth
    colorToGray(inImage); // Convert input image into b&w image

    label(inImage, outImage); // Call Label function
    outImage.WriteToFile(outputfile); // Output new image
    return 0;

}
void label(BMP &inImage, BMP &outImage){

    // Set variables for width and height
    int width = inImage.TellWidth(); int height = inImage.TellHeight();

    // Intialize 2D boolean array
    // Set each index to false
    bool visited[width][height];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            visited[i][j] = false;
        }
    }
    //
    outImage.SetSize(width,height); // Set output image size
    outImage.SetBitDepth(24); // Set Bit Depth

    // Copy input image to output image
    RangedPixelToPixelCopy(inImage, 0, width, height, 0, outImage, 0, 0);

    // Initialize variables for counting lines and characters
    int lineCount = 0; int charCount = 0;
    // Initialize coordinates for lowest x and y values
    // and highest x and y values
    int lowX = 0; int lowY = 0; int highX = 0; int highY = 0;

    // Scan through the image row by row (height by width)
    for(int i = 0; i < height -1; i++) {
        for (int j = 0; j < width -1; j++) {
            // Use Temp to grab contents of each pixel (x,y)
            RGBApixel Temp = outImage.GetPixel(j, i);
            if (Temp.Red < 20 && Temp.Green < 20 && Temp.Blue < 20) {// If pixel is black
                charCount++; // Count character
                if (i > highY) // Count line if there's a higher height
                    lineCount++;
                // Set lowest x and y values
                // Set highest x and y values
                lowX = j; lowY = i;
                highX = j; highY = i;

                // Initialize queue of points,
                // insert the first point to queue,
                // and set it to true
                queue Q;
                Q.insert(j, i);
                visited[j][i] = true;
                auto *p = new point(j, i);

                // Run queue through while loop to
                // to start BFS on the graph to
                // identify all the pixels connecting
                // the starting pixel. This connect
                // the pixels in the letters
                while (!Q.isEmpty()) {
                    *p = Q.del();
                    // Get values of the first black pixel
                    int x1 = p->getx();
                    int y1 = p->gety();
                    // Turn the pixel green
                    outImage(x1, y1)->Red = 0;
                    outImage(x1, y1)->Blue = 0;
                    outImage(x1, y1)->Green = 255;

                    // Replace lowest or highest x and y
                    // values if conditions apply
                    if (x1 < lowX) lowX = x1;
                    if (x1 > highX) highX = x1;
                    if (y1 < lowY) lowY = y1;
                    if (y1 > highY) highY = y1;

                    // Scan the 8 neighboring pixels		
                    for (int jj = -1; jj <= 1; jj++) {
                        for (int ii = -1; ii <= 1; ii++) {
                            if (jj == 0 && ii == 0) // Skip center point
                                continue;
                            int neighborX = x1 + jj; // Neighbor X value
                            int neighborY = y1 + ii; // Neighbor Y value
                            if (isValid(neighborX, neighborY, width, height)) { // Check boundaries
                                if (!visited[neighborX][neighborY]) { // Check if neighbor point is notvisited
                                    visited[neighborX][neighborY] = true;
                                    // Check if neighbor is a black pixel .If so push to queue
                                    // b/c it is part of the letter
                                    RGBApixel Temp2 = outImage.GetPixel(neighborX, neighborY);
                                    if (Temp2.Red < 20 && Temp2.Green < 20 && Temp2.Blue < 20)
                                        Q.insert(neighborX, neighborY);
                                }
                            }
                        }
                    }

                }
                // Use drawH to draw horizontal lines and
                // drawV for vertical lines to create the box
                drawH(lowX - 1, highX + 1, lowY - 1, outImage); // Top 
                drawH(lowX - 1, highX + 1, highY + 1, outImage);// Bottom 
                drawV(lowY - 1, highY + 1, lowX - 1, outImage); // Left
                drawV(lowY - 1, highY + 1, highX + 1, outImage); // Right

            }
            else { // If the pixel is white set as visited
                visited[j][i] = true;
            }
        }
    }
    cout << "The number of lines in this image is " << lineCount << " lines" << endl;
    cout << "The number of characters in this image is " << charCount << " characters" << endl;
}
bool isValid(int x, int y, int width, int height){
    // Check boundaries
    return x >= 0 && y >= 0 && x < width && y < height;
}
void colorToGray(BMP & Output) {
    int picWidth = Output.TellWidth();
    int picHeight =Output.TellHeight();
    Output.SetBitDepth(1); //compression happens here
    for (int i = 0; i < picWidth-1; ++i)
        for (int j = 0; j < picHeight-1; ++j) {
            int col = 0.1* Output(i, j)->Blue + 0.6*Output(i,j)->Green +0.3* Output(i,j)->Red;
            if (col > 127) {
                Output(i,j)->Red = 255;
                Output(i,j)->Blue = 255;
                Output(i,j)->Green = 255;
            }
        }
}
void drawH(int x1, int x2, int y, BMP &outImage){
    // Interate from x1 to x2 to color
    // each pixel red to form a horizontal line
    // (x1, y) ... (x2, y) 
    for (int i = x1; i <= x2; i++){
        outImage(i, y)->Red = 255;
        outImage(i, y)->Blue = 0;
        outImage(i, y)->Green = 0;
    }
}
void drawV(int y1, int y2, int x, BMP & outImage){
    // Interate from y1 to y2 to color
    // each pixel red to form a horizontal line
    // (x, y1) ... (x, y2)
    for(int i = y1; i <= y2; i++){
        outImage(x, i)->Red = 255;
        outImage(x, i)->Blue = 0;
        outImage(x, i)->Green = 0;
    }
}
