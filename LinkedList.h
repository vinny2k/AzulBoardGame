#ifndef LINKED_LIST_H
#define LINKED_LIST_H 

#include "Tile.h"

#include <exception>
#include <vector>
#include <algorithm>
#include <string>
// Creation of node class
class Node {
public:
   Node(Tile* tile, Node* next);

   Tile* tile;
   Node* next;
};
// Creation of Linked list
class LinkedList {
public:
   LinkedList();
   ~LinkedList();

   /**
    * Return the size of the Linked List
    */
   int size();

   /**
    * Gets the tile at the index
    */
   Tile* get(int index);

   /**
    * Adds a value to the back of the Linked List
    */
   void addBack(Tile* colour);

   /**
    * Adds a value to the front of the Linked List
    */
   void addFront(Tile* colour);

   /**
    * Remove value at the back of the Linked List
    */
   void removeBack();

   /**
    * Remove the value at the front of the Linked List
    */
   void removeFront();

   /**
    * Removes all values from the Linked List
    */
   void clear();

   /**
   * Milestone 3 - Enhancement
   * Shuffles the Linked List with a given seed
   */
   void shuffle(int seed);

   std::string getTilesAsString();

private:
   Node* head;
};

#endif // LINKED_LIST_H
