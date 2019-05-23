#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
//#include "scan.cpp"


using namespace std;
vector<string>breakTokens (string input);

class Stack;

class Node {

public:
    Node(int key1){
        key = key1;
        tag = 0;
        down = NULL;
        next = NULL;
    }

    Node(Node* dptr, Node* nptr) {
        tag = 1;
        down = dptr;
        next = nptr;
    }
    void setTag(int x){
        tag = x;
    }
    int getTag(){
        return tag;
    }
    void setKey(int k) {
        key = k;
    }

    void setDown(Node* ptr) {
        down = ptr;
    }

    void setNext(Node* ptr) {
        next = ptr;
    }

    int getKey() {
        return key;
    }

    Node* getDown() {
        return down;
    }

    Node* getNext() {
        return next;
    }

    int size() {
        if (this == NULL)
            return 0;
        else if (this->tag == 0) return 1;
        else
            return down->size() + next->size();
    }

    void update(int j, int k) {
        if(this->isEmpty()) {
            cout << "List is empty!\n";
            return;
        } else if (this->tag == 0){
            this->key = k;
        } else {
            int s = this->down->size();
            if (j <= s)
                this->down->update(j, k);
            else
                this->next->update(j - s, k);
        }
        // to be completed
    }

    bool isEmpty() {
        return this == NULL;
    }

    void print(int depth) {
        if (this == NULL) return;
        if (tag == 0) {
            cout << "<" << key << ":" << depth << ">  " ;
        }
        else {
            down->print(depth+1);
            next->print(depth);
        } // end else
    } // end print

private:
    int tag;
    int key;
    Node* down;
    Node* next;
};

class Stack {

private:
    int maxTop;// max stack size = size - 1
    int top;// current top of stack
    Node* values[1000];// element array

public:

    bool IsEmpty() { return top == -1; }
    bool IsFull() { return top == maxTop; }

    Stack() {
        top=-1;
        maxTop= 999;
    }

    void Push(Node* x) {
        if (IsFull())  // if stack is full, print error
            cout << "Error: the stack is full." << endl;
        else {
            values[++top]= x;
        }
    }

    Node*  Pop() {
        if (IsEmpty()) { //if stack is empty, print error
            cout << "Error: the stack is empty." << endl;
            return NULL;
        }
        else {
            return values[top--];
        }
    }

    Node* Top() {
        if (IsEmpty()) {
            cout << "Error: the stack is empty." << endl;
            return NULL;
        }
        else
            return values[top];
    }
};

int convert(string x) {
    // converts a string rep of decimal integer to an int
    return atoi(x.c_str());
}
Node* create (vector<string> T) {
    Stack S;
    for (int k = 0; k < T.size(); k++){
        if(T[k] == "[") {
            Node *m = new Node(nullptr, nullptr);
            m->setTag(-1);
            S.Push(m);
        } else if (T[k] == "]"){ // ']'
            Node *temp = new Node(nullptr, nullptr);
            while (S.Top()->getTag() != -1){
                Node *k1 = S.Pop();
                Node *N = new Node(k1 , temp);
                temp = N;
            }
            S.Pop();
            S.Push(temp);

        } else if(T[k] >= "0" or T[k] <= "9" or T[k] == "-"){ //Integers
            int digit;
            digit = convert(T[k]);
            Node *n = new Node(digit);
            S.Push(n);
        } else {
	    cout << "Invalid element\n";
	    break;
	}
    }
    return S.Pop();
    //return NULL; // to be completed. Takes as input a vector of strings and builds a generalized list
}

int main() {
    cout << "Input generalized list\n";
    string input;

    getline (cin,input);
    vector<string> arrayOfTokens = breakTokens(input);
    string printString = input;
    //for (int i = 0; i < arrayOfTokens.size(); i++)
    //   cout << arrayOfTokens[i] << ", ";*/

    Node* temp = create(arrayOfTokens);
    cout << "The input list (with depth for each key):\n";
    temp->print(0);
    cout << "\n";
    string userInput;
    string userPrompt ="What would you list to do?\n"
                       "'u' : Update an element\n"
                       "'p' : Print input list\n"
                       "'q' : Quit the program\n ";
    cout << userPrompt;
    while(userInput != "q"){
        cin >> userInput;
        if (userInput == "u") {
            int inputNum;
            int updatedNum;
            cout << "Which element would you like to update? ";
            cin >> inputNum;
            cout << "What would you like to update it to? ";
            cin >> updatedNum;
            cout << "Updated list is: \n";
            temp->update(inputNum, updatedNum);
            temp->print(0);
            cout << "\n";
        } if (userInput == "p")
            cout << printString << "\n";
        if (userInput == "q")
            break;
        cout << userPrompt;
    }
    return 0;
}
vector<string> breakTokens(string input){
    int leftBracketCount = 0;
    int rightBracketCount = 0;
    int numCount = 0;
    vector<string>Tokens;
    stringstream ss;
    ss << input;
    char c;
    while(ss >> c){
        if (c == '[') {
            Tokens.emplace_back("[");
            leftBracketCount++;
        }
        else if (c == ']') {
            Tokens.emplace_back("]");
            rightBracketCount++;
        }
        else if (c == (' ' or ','))
            continue;
        else if (c == '-' or isdigit(c)){
            char d;
            string digit;
            digit += c;
            while(ss.get(d)) {
                if (!isdigit(d))
                    break;
                else
                    digit += d;
            }
            ss.putback(d);
            Tokens.push_back(digit);
            numCount++;
        }
    }

    return Tokens;
}
