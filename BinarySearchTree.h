#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Tile.h"

#include <iostream>


/**
* Enhancement class containing the TreeNode class and the BinarySearchTree class
*/

class TreeNode {
public:
    TreeNode(int count, Tile* tile, TreeNode* parent, TreeNode* left, TreeNode* right);
    TreeNode(TreeNode& other);
    ~TreeNode();

    int count;
    Tile* tile;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
};


class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    /**
    * Returns the root of the bst
    */
    TreeNode* getRoot();

    /**
    * Inserts a node with given tile into the bst
    */
    void insert(Tile* tile);
    TreeNode* insert(TreeNode* node, Tile* tile);

    /**
    * Prints all nodes in the tree from min to max
    */
    void printTreeInOrder();
    void printTreeInOrder(TreeNode* node);

    /**
    * Returns true if a node with given tile exists in bst
    */
    bool search(Tile* tile);
    TreeNode* search(TreeNode* node, Tile* tile);

    /**
    * Returns an integer value of the minimum node's tile's colour
    */
    int findMin();
    int findMin(TreeNode* node);
    
    /**
    * Returns an integer value of the maximum node's tile's colour
    */
    int findMax();
    int findMax(TreeNode* node);

    /**
    * Returns an integer value of the next node's tile's colour, 
    * given that the next node's tile's colour is minimally greater than the given tile's colour
    */
    int successor(Tile* tile);
    int successor(TreeNode* node);

    /**
    * Returns an integer value of the next node's tile's colour, 
    * given that the next node's tile's colour is minimally lesser than the given tile's colour
    */
    int predecessor(Tile* tile);
    int predecessor(TreeNode* node);

    /**
    * Removes a node with the given tile
    */
    void remove(Tile* tile);
    TreeNode* remove(TreeNode* node, Tile* tile);

    /**
    * Returns a leaf node from the bst
    */
    TreeNode* visitLeaf(TreeNode* node);

private:
    TreeNode* root;

};
#endif // BINARYSEARCHTREE_H