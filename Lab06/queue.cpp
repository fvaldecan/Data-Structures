/* Name: Franco Dominic Valdecanas
 * Date: March 6, 2019
 * Program: queue.cpp
 * Description:
 * The goal of this program is to find the shortest path through a maze.
 * The maze is represented by an image where the path is allowed through
 * white pixels but blocked by black pixels. The maze can be viewed as a
 * graph where each pixel is a vertex (x, y). Given a starting vertex s and
 * a destination t, the goal is to find the shortest path from s to t. This
 * program will take an input file containing an image, x and y coordinates
 * for s and t. It will output an image where the shortest path is drawn in
 * red. It will also output the length of the shortest path from start to
 * destination and the total number of pixels that entered the queue.
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

void BFS (BMP &inImage, BMP &outImage, point *s, point *t, int count);
void colorToGray(BMP & Output);
int main(int argc, char** argv){
	const char* inputfile;
	const char* outputfile;

	// Intialize BMP input and output images
	BMP inputMaze;
	BMP outputMaze;


	if (argc > 1) {
        inputfile = argv[1];
    }
    else inputfile = "in.bmp";

    if (argc > 2) outputfile = argv[2];
    else outputfile = "out.bmp";

	inputMaze.ReadFromFile(inputfile); // Read in image (maze) file

	//Store image width and height as variables
	int width = inputMaze.TellWidth(); int height = inputMaze.TellHeight();


	inputMaze.SetBitDepth(24); // Set input image bit depth
	colorToGray(inputMaze); // Turn input image into black and white

	// Prompt user to input x and y coordinates for start point
	int sX; int sY;
	bool validPixel1;
	while(!validPixel1) {
		//Will continue prompting until user enters a valid s point

		cout << "Enter x-coordinate for start point: ";
		cin >> sX;
		cout << "Enter y-coordinate for start point: ";
		cin >> sY;
		cout << "Start point: " << '(' << sX << ", " << sY << ")\n";
		// Temp will get information on the pixel including color
		RGBApixel Temp = inputMaze.GetPixel(sX,sY);
		//Checks to see if the pixel is valid (Not black and not
		//out of bounds
		if(Temp.Red != 0 && Temp.Green != 0 && Temp.Blue != 0 ||
		sX < 0 || sX > width || sY < 0 || sY > height  ) {
			validPixel1 = true;
			break;
		}
		cout << "Enter a different point!\n";
		cout << "Point is either out of bounds or a black pixel. \n";
		validPixel1 = false;
	}

	// Prompt user to input x and y coordinates for destination point
	int tX; int tY;
	bool validPixel2;
	while(!validPixel2) {
		//Will continue prompting until user enters a valid t point

		cout << "Enter x-coordinate for destination point: ";
		cin >> tX;
		cout << "Enter y-coordinate for destination point: ";
		cin >> tY;
		cout << "Destination point: " << '(' << tX << ", " << tY << ")\n";
		// Temp will get information on the pixel including color
		RGBApixel Temp = inputMaze.GetPixel(sX,sY);
		//Checks to see if the pixel is valid (Not black and not
		//out of bounds
		if(Temp.Red !=  0 && Temp.Green != 0 && Temp.Blue != 0 ||
		sX < 0 || sX > width || sY < 0 || sY > height  ) {
			validPixel2 = true;
			break;
		}
		cout << "Enter a different point!\n";
		cout << "Point is either out of bounds or a black pixel. \n";
		validPixel2 = false;
	}

	// Initialize start point s and destination point t
	point *s = new point(sX, sY); point *t = new point(tX, tY);

	int count = 0; // Initialize count for total count of pixels

	// Run through the Breadth First Search(BFS) function
	// BFS will be used to find the shortest path
	BFS(inputMaze, outputMaze, s, t, count);

	// Output the image drawing (in red pixels) the shortest
	outputMaze.WriteToFile("out.bmp");
	return 0;
}
void BFS (BMP &inImage, BMP &outImage, point *s, point *t, int count){
	// BFS will keep track of the distance and parents between vertices
	// using arrays and pointers. s is the start, t is the destination

	//Store image width and height as variables
	int width = inImage.TellWidth();
	int height = inImage.TellHeight();

	outImage.SetSize(width, height); //Set the width and height for output image
	outImage.SetBitDepth(24); // Set bit depth for output image

	// Copy input image to output image
	RangedPixelToPixelCopy(inImage, 0, width, height, 0, outImage, 0, 0);
	queue Q; //Initialize queue
	Q.insert(s); // Insert first point into queue
	count++; // Count starting pixel

	bool visited[width][height]; // Initialize Visited 2D Array
	bool blocked[width][height]; // Initialize Blocked Pixels Array
	int distance[width][height]; // Initialize Distance Array
	point *parent[width][height];// Initialize Pointer Parent Array
	for (int i = 0; i < width; i++){
		for(int j = 0; j <height; j++){
			RGBApixel Temp = outImage.GetPixel(i,j);
			if(Temp.Red < 20 && Temp.Green < 20 && Temp.Blue < 20)
				blocked[i][j] = true; // Set pixels that are black to true
			else {
				distance[i][j] = 0; // Set all pixels distance to 0
				blocked[i][j] = false; // Set pixels that are not black to false
				visited[i][j] = false; // Set all pixels to false for not visited
				parent[i][j] = new point(0,0); // Set pixels as pointers
			}

		}
	}

	// Save x and y values for start pointer
	int sX = s->getx(); int sY = s->gety();

	// Save x and y values for destination pointer
	int tX = t->getx(); int tY = t->gety();

	point *u = new point(0, 0); //Create pointer u for the queue
	distance[sX][sY] = 0; // Set distance of start point to 0
	visited[sX][sY] = true; // Set start point to visited

	while((!Q.isEmpty()) && (!visited[tX][tY])) {
	    // Will continue to loop until the queue is empty and destination is visited
        *u = Q.del(); // Pop the queue

        if ((!visited[u->getx()][u->gety() - 1]) &&
            (!blocked[u->getx()][u->gety() - 1])) {
            //Upper Neighbor vertex
            //if not visited and not out of bounds and not blocked by wall (black pixel)

            point *vUp = new point(u->getx(), u->gety() - 1); //Set Upper Neighbor vertex coordinate
            visited[u->getx()][u->gety() - 1] = true; // Set Upper Neighbor to true;
            distance[u->getx()][u->gety() - 1] = distance[u->getx()][u->gety()] + 1; // Increment the distance
            *parent[vUp->getx()][vUp->gety()] = *u;// Point Upper Neighbor pointer to original pointer u
            Q.insert(vUp);// Push Upper Neighbor vertex to queue
            count++; //Count pixel in Q
        } if ((!visited[u->getx() - 1][u->gety()]) &&
                   (!blocked[u->getx() - 1][u->gety()])) {
            //Left Neighbor pixel
            //if not visited and not out of bounds and not blocked by wall (black pixel)

            point *vLeft = new point(u->getx() - 1, u->gety()); //Set Left Neighbor vertex coordinate
            visited[u->getx() - 1][u->gety()] = true; // Set Left Neighbor to true;
            distance[u->getx() - 1][u->gety()] = distance[u->getx()][u->gety()] + 1; // Increment the distance
			*parent[vLeft->getx()][vLeft->gety()] = *u; // Point Left Neighbor pointer to original pointer u
            Q.insert(vLeft); // Push Left Neighbor vertex to queue
            count++; //Count pixel in Q
        } if ((!visited[u->getx()][u->gety() + 1]) &&
                   (!blocked[u->getx()][u->gety() + 1])) {
            //Down Neighbor vertex
            //if not visited and not out of bounds and not blocked by wall (black pixel)

            point *vDown = new point(u->getx(), u->gety() + 1); //Set Down Neighbor vertex coordinate
            visited[u->getx()][u->gety() + 1] = true; // Set Down Neighbor to true;
            distance[u->getx()][u->gety() + 1] = distance[u->getx()][u->gety()] + 1; // Increment the distance
			*parent[vDown->getx()][vDown->gety()] = *u; // Point Down Neighbor pointer to original pointer u
            Q.insert(vDown); // Push Down Neighbor vertex to queue
            count++; //Count pixel in Q

        } if ((!visited[u->getx() + 1][u->gety()]) &&
                   (!blocked[u->getx() + 1][u->gety()])) {
            //Right Neighbor vertex
            //if not visited and not out of bounds and not blocked by wall (black pixel)

            point *vRight = new point(u->getx() + 1, u->gety()); //Set Right Neighbor vertex coordinate
            visited[u->getx() + 1][u->gety()] = true; // Set Right Neighbor to true;
            distance[u->getx() + 1][u->gety()] = distance[u->getx()][u->gety()] + 1; // Increment the distance
			*parent[vRight->getx()][vRight->gety()] = *u; // Point Right Neighbor pointer to original pointer u
            Q.insert(vRight); // Push Right Neighbor vertex to queue
            count++; //Count pixel in Q
        }
    }
	point *v = new point(tX, tY);//Set vertex v with destination coordinates

	if(visited[tX][tY]){ //if destination vertex was visited
	    while (v != s){
	        //Will loop until vertex v traces back to start pixel
	    	if(v == nullptr) //If v points to nothing then it's done
	    		break;
	    	if(v->getx() > 0 && v->getx() < width
	    	&& v->gety() > 0 && v->gety() < height){
	    	    // if x or y coordinates are in bounds
				outImage(v->getx(), v->gety())->Red = 255;
				outImage(v->getx(), v->gety())->Blue = 0;
				outImage(v->getx(), v->gety())->Green = 0;
			}
			v = parent[v->getx()][v->gety()]; //Make point v to point parent
		}
		cout << "The shortest distance is " << distance[tX][tY] << endl;
		cout << "The number of pixels in the queue is " << count << endl;
	}else {
		cout << "No path from start point s, (" << sX << " ," << sY << ")\n";
		cout << "to destination point t, ("<< tX << " ," << tY << ")\n";
	}
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

 
