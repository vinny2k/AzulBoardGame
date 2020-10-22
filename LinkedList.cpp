#include "LinkedList.h"

// Tile and next are needed at construction of object
Node::Node(Tile* tile, Node* next) :
   tile(tile),
   next(next)
{} 

LinkedList::LinkedList() 
{
   head = nullptr;
}
// Using the clear method to delete the linked list
LinkedList::~LinkedList() {
   clear();
}
// Loops through the list until the null at the end of the list is reached
int LinkedList::size() {
   int count = 0;
   Node* current = head;
   while(current != nullptr) {
      ++count;
      current = current->next;
   }
   return count;
}
// Gets tile at certain index, loops through until at index
Tile* LinkedList::get(int index) {
   std::string returnval;
   int count = 0;
   Node* current = head;
   Tile* tilecol;
   std::string colstr;
   if (index < size()) {
      while(count < index) {
         ++count;
         current = current->next;
      }
      tilecol = current->tile;
   } else {
      throw std::out_of_range("Linked List: index out of range");
   }
   return tilecol;
}
// Adding to the front of the list
void LinkedList::addFront(Tile* tilec) {
   if (head == nullptr) {
      Node* toAdd = new Node(tilec, nullptr);
      head = toAdd;
   } else {
      Node* current = head;
      Node* toAdd = new Node(tilec, current);
      head = toAdd;
   }
}
// Adding to back of linked list
void LinkedList::addBack(Tile* tilec) {
   Node* toAdd = new Node(tilec, nullptr);
   if (head == nullptr) {
      head = toAdd;
   } else {
      Node* current = head;
      while(current->next != nullptr) {
         current = current->next;
      }
      current->next = toAdd;
   }
}
// Removing the back of the linked list
void LinkedList::removeBack() {
   if (head == nullptr) {
      throw std::runtime_error("There is noting to remove");
   } else {
      Node* current = head;
      Node* prev = nullptr;
      while(current->next != nullptr) {
         prev = current;
         current = current->next;
      }

      prev->next = nullptr;
      delete current->tile;
      delete current;
   }
}
// Removing the front of the linked list
void LinkedList::removeFront() {
   if (head != nullptr){
       Node* current = head;
       head = head->next;

       delete current->tile;
       delete current;
   } else {
      throw std::runtime_error("There is noting to remove");
   }
}
// Looping the remove front to clear the linked list
void LinkedList::clear() {
   while(head != nullptr){
       removeFront();
   }
}

void LinkedList::shuffle(int seed) {
   // initialise empty vector
   std::vector<Tile*> temp;
   
   // copies tiles in head node to the vector
   while (head != NULL) {
      Node* current = head;
      head = head->next;
      temp.push_back(current->tile);
   }

   
   std::srand(seed);
	for (unsigned int i = 0; i < temp.size() - 1; i++)
	{
		// present at current index i
		int j = i + rand() % (temp.size() - i);
		std::swap(temp[i], temp[j]);
	}

   for (unsigned int i = 0; i < temp.size(); ++i) {
      addBack(temp.at(i));
   }
}

std::string LinkedList::getTilesAsString() {
   std::string tiles = "";
   Node* current = head;
   while(current != nullptr) {

      tiles += current->tile->getletter();

      current = current->next;
   }

   tiles.erase(remove(tiles.begin(), tiles.end(), ' '), tiles.end());
   
   return tiles;
}