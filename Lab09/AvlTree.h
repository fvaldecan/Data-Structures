#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x )
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    /**
     * Print the tree contents in sorted order.
     */
    void printTree(int maxWordSize ) const //ostream & out = cout,
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root,  maxWordSize );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x, int lineNumber)
    {
        insert( x, root, lineNumber );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
    int countNodes(){

        countNodes(root);
    }
    int height(){
        height(root);
    }
    void printSearchLines(string searchWord){
        printSearchLines(root, searchWord);
    }
    int printbuildComparisons(){
        return printbuildComparisons(root);
    }
    int printsearchComparisons(){
        return printsearchComparisons(root);
    }
    int printRotationsCount(){
        return printRotationsCount(root);
    }
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        vector<int>lineNumberList;
        int nodeHeight;
        AvlNode( const Comparable & theElement, AvlNode *lt, AvlNode *rt, int nodeHeight)
          : element{ theElement }, left{ lt }, right{ rt } { }

        AvlNode( Comparable && theElement, AvlNode *lt, AvlNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    AvlNode *root;
    int buildComparisons = 0;
    int searchComparisons = 0;
    int rotationsCount = 0;
    int printbuildComparisons(AvlNode *t){
        return buildComparisons;
    }
    int printsearchComparisons(AvlNode *t){
        return searchComparisons;
    }
    int printRotationsCount(AvlNode *t){
        return rotationsCount;
    }

    void printSearchLines(AvlNode *t, string searchWord){
        string lineNumbers;
        if( t->element == searchWord){
            for(int i = 0; i < t->lineNumberList.size();i++) {
                if (i == t->lineNumberList.size() - 1)
                    lineNumbers += to_string(t->lineNumberList[i]);
                else {
                    lineNumbers += to_string(t->lineNumberList[i]);
                    lineNumbers += ", ";
                }
            }
        }
        else if( searchWord < t->element )
            return printSearchLines( t->left, searchWord );
        else if( t->element < searchWord )
            return printSearchLines( t->right,searchWord );
        cout << lineNumbers;

    }
    int countNodes(AvlNode *t){
        if (t == NULL)
            return 0;
        else
            return 1 + countNodes(t->left) + countNodes(t->right);
    }

    int height(AvlNode *t) const {
        if(t == NULL)
            return -1;
        return 1 + max(height(t->left), height(t->right));
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t, int lineNumber)
    {
        if( t == nullptr ) {
            t = new AvlNode{x, nullptr, nullptr,0};
            t->lineNumberList.push_back(lineNumber);
        }
        else if( x < t->element ) {
            buildComparisons += 1;
            insert(x, t->left, lineNumber);
        }
        else if( t->element < x ) {
            buildComparisons += 2;
            insert(x, t->right, lineNumber);
        }
        else if(t->element == x){
            buildComparisons += 2;
            t->lineNumberList.push_back(lineNumber);
        }
        balance(t);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{std::move(x), nullptr, nullptr,0};
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, AvlNode *t )
    {
        if( t == nullptr )
            return false;
        else if( x < t->element ) {
            searchComparisons += 1;
            return contains(x, t->left);
        }
        else if( t->element < x ) {
            searchComparisons += 2;
            return contains(x, t->right);
        }
        else {
            searchComparisons += 2;
            return true;    // Match
        }
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t, int maxWordSize ) const // ostream & out,
    {
        if( t != nullptr )
        {
            cout << setw(maxWordSize) << left;
            printTree( t->left, maxWordSize );
            cout <<  t->element;
            for(int i = 0; i < t->lineNumberList.size();i++) {
                if(i == t->lineNumberList.size() -1)
                    cout << t->lineNumberList[i];
                else
                    cout << t->lineNumberList[i] << ", ";
            }
            cout << endl;
            printTree( t->right, maxWordSize );
            cout << setw(maxWordSize) << left;

        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ) };
    }
    static const int ALLOWED_IMBALANCE = 1;
    void balance(AvlNode *&t){
        if (t == NULL)
            return;
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
            if (height(t->left->left) >= height(t->left->right)) // Case 1
                rotateWithLeftChild(t);
            else // Case 2
                doubleWithLeftChild(t);
        } else{
            if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE){
                if(height(t->right->right) >= height(t->right->left)) // Case 3
                    rotateWithRightChild(t);
                else // Case 4
                    doubleWithRightChild(t);
            }
            t->nodeHeight = height(t);

        }
    }
    void rotateWithLeftChild(AvlNode *& k2){
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->nodeHeight = height(k2);
        k1->nodeHeight = height(k1);
        k2 = k1;
        rotationsCount++;

    }
    void rotateWithRightChild(AvlNode *& k2){
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->nodeHeight = height(k2);
        k1->nodeHeight = height(k1);
        k2 = k1;
        rotationsCount++;

    }
    void doubleWithLeftChild(AvlNode *&k3){
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void doubleWithRightChild(AvlNode *&k3){
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);

    }



};

#endif
