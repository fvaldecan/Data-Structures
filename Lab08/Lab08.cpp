/* Name: Franco Dominic Valdecanas
* Date: April 2, 2019
* Program: Lab08.cpp
* Description:
* This program will read an input file specified by the user, and build the index table,
* and reports the following: the number of distinct words (the number of nodes in the tree),
* the height of the tree, and the total CPU time to complete index building. Display the
* index in an organized format. Search for a word. (Display the line numbers containing the
* word and the frequency.) Save the index (as a specified text file).
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "BinarySearchTree.h"
using namespace std;
int buildTree(BinarySearchTree<string> * BST, const string &inputfile);
void printOutput(BinarySearchTree<string> * BST, int numWords, double time);
int main(int argc, char** argv) {
    const char *inputfile;
    if (argc > 1) {
        inputfile = argv[1];
    } else inputfile = "in.txt";

    //Intialize Binary Search Tree
    BinarySearchTree<string> * BST;
    BST = new BinarySearchTree<string>();

    // Get longest word size from Build Tree function
    int maxWordSize = buildTree(BST, inputfile);

    // Prompt options for the user
    cout << endl;
    cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";

    int choice;
    string searchWord;
    string file;
    bool breakflag = false;
    cin >> choice;
    while(choice != 4) {
        switch (choice) {
            case 1: // Prompt Index
                cout << "Binary Search Tree Index:\n";
                cout << "-------------------------\n";
                BST->printTree(maxWordSize);
                break;
            case 2: // Search for a word in the tree
                cout << "Search word? ";
                cin >> searchWord;
                if(BST->contains(searchWord)) {
                    cout << "Line numbers<BST>: ";
                    BST->printSearchLines(searchWord);
                    cout << endl;
                } else
                    cout << "The word is not in the document\n";
                break;
            case 3: { // Save Index

                cout << "What would you like to name your file (*.txt)?  ";
                cin >> file;
                std::streambuf *psbuf, *backup;
                std::ofstream filestr;
                filestr.open (file);
                backup = std::cout.rdbuf(); // back up cout's streambuf
                psbuf = filestr.rdbuf(); // get file's streambuf
                std::cout.rdbuf(psbuf); // assign streambuf to cout

                cout << "Binary Search Tree Index:\n";
                cout << "-------------------------\n";
                BST->printTree(maxWordSize);

                std::cout.rdbuf(backup); // restore cout's original streambuf
                filestr.close();

                cout << "Index saved into " << file << endl;
                break;
            }
            case 4: // Quit
                cout << endl;
                return 0;
            default: // When user input isn't one of the options
                cout << "Invalid response!\n";
                breakflag = true; // Set true to queue exit
                break;
        }
        if(breakflag) // Exit out of loop
            break;

        // Continue to prompt options and ask for user input
        cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
        cin >> choice;
    }
    return 0;
}

int buildTree(BinarySearchTree<string> * BST, const string &inputfile){
    // Builds the Binary Search Tree

    // Initialize counters
    int lineNumber = 0; int wordCount = 0;
    int maxWordSize = 0; double finish_time;

    // Read input file in fstream
    ifstream readfile(inputfile);
    string str;
    double start_time = clock(); // Start the clock
    while (getline(readfile, str)) { // Read file line by line
        lineNumber++; // Count number of lines

        // Read word by word from str stream
        string word; stringstream iss(str);
        while (iss >> word){
            int tempSize = 0; // Temp used to count characters
            wordCount++; // Count number of total words

            // Scan through the word checking
            // for unneeded characters and
            // counting characters
            string newWord;
            for (char i : word) {
                if (isdigit(i)) {
                    for (char j : word) {
                        newWord += j;
                        tempSize++;
                    }
                    break;
                }
                if (i == '.' or i == ',' or i == ' ')
                    continue;
                else {
                    newWord += i;
                    tempSize++;
                }
            }

            // Find the longest word
            if(tempSize > maxWordSize)
                maxWordSize = tempSize;

            //Skip empty word
            if(newWord.empty())
                continue;

            // Insert word and line number in tree
            BST->insert(newWord, lineNumber);
        }
    }
    maxWordSize += 4; // Add 4 spaces or tab (\t) to the size
    finish_time = clock(); // Stop clock
    double time = (finish_time - start_time)/ CLOCKS_PER_SEC; // Calculate the amount of time
    printOutput(BST,wordCount,time); // Print statistics
    return maxWordSize;
}
void printOutput(BinarySearchTree<string> * BST, int numWords,double time){
    // Prints out the details of the binary search tree
    cout << setw(20) << left << "Total number of words: " << setw(19) << right << numWords << endl; //<< setw(21) << left << endl;
    cout << setw(20) << left <<"Total number of distinct words:  " << setw(9) << right << BST->countNodes() << endl;
    cout << setw(20) << left <<"Time taken to build index using BST is: " << time << " sec\n";
    cout << setw(20) << left <<"Height of BST tree is: " << setw(19) << right <<  BST->Treeheight() << left << endl;
}
