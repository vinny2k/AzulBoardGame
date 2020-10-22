#ifndef BST_FACTORY_H
#define BST_FACTORY_H

#include "BinarySearchTree.h"

#include <iostream>
#include <iostream>

#define TILES_IN_FACTORY 4

/**
* Enhancement class to replace previous factory with a bst
*/
class BSTFactory {
public:
    BSTFactory();
    ~BSTFactory();

    /**
    * Get a tile if it exists
    */
    Tile* getTile(Colour colour);

    /**
    * Returns true if the bst contains given tile
    */
    bool contains(Colour colour);

    /**
    * Add a tile to the factory
    */
    void add(Tile* tile);

    /**
    * Remove a Tile from the factory
    */
    void remove(Colour colour);

    /**
    * Returns the bst
    */
    BinarySearchTree* getBST();

    /**
    * Print all items in factory
    */
    void printletters();

    /**
    * Checks if factory is empty
    */
    bool isEmpty();

    /**
    * returns count of the given tile in the factory
    */
    int getCount(Colour colour);

private:
    BinarySearchTree* bstFac;

};
#endif // BST_FACTORY_H