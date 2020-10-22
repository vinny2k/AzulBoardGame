#include "BSTFactory.h"

BSTFactory::BSTFactory() {
    bstFac = new BinarySearchTree();
}

BSTFactory::~BSTFactory() {
    delete bstFac;
    bstFac = nullptr;
}

Tile* BSTFactory::getTile(Colour colour) {
    Tile* temp = nullptr;
    // initialise givenTile as a new tile with colour colour
    Tile* givenTile = new Tile(colour);

    // if a node with tile equal to givenTile exists in the bst
    if (bstFac->search(givenTile)) {
        // initialise temp as a copy of givenTile
        temp = new Tile(*givenTile);
        // remove a node with tile equal to givenTile from bst
        bstFac->remove(givenTile);
    }
    // delete givenTile and return temp
    delete givenTile;
    return temp;
}

bool BSTFactory::contains(Colour colour) {
    // initialise temp as a new tile with colour colour
    Tile* temp = new Tile(colour);
    bool found = false;

    // if bst contains a node with tile equal to temp
    if (bstFac->search(temp)) {
        // set found to true
        found = true;
    }

    // delete temp and return found
    delete temp;
    return found;
}

void BSTFactory::add(Tile* tile) {
    // insert a new tile copying given tile into bst
    bstFac->insert(new Tile(*tile));
}

void BSTFactory::printletters() {
    // calls bst print function
    bstFac->printTreeInOrder();
}

bool BSTFactory::isEmpty() {
    // returns true if the root is nullptr
    return bstFac->getRoot() == nullptr;
}

void BSTFactory::remove(Colour colour) {
    // instantiates temp as a new tile of given colour
    Tile* temp = new Tile(colour);
    // remove any nodes from bst if they have the same tile as temp
    bstFac->remove(temp);
    // delete temp
    delete temp;
}

int BSTFactory::getCount(Colour colour) {

    int count = 0;
    // instantiates temp as a new tile of given colour
    Tile* temp = new Tile(colour);

    // if bst contains a node with tile equal to temp
    if (bstFac->search(temp)) {
        // set count to the count of that node
        count = bstFac->search(bstFac->getRoot(), temp)->count;
    }

    return count;
}

BinarySearchTree* BSTFactory::getBST() {
    // return the bst
    return bstFac;
}