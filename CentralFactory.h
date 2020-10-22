#ifndef COSC_ASSIGN_TWO_CENTRAL_FACTORY
#define COSC_ASSIGN_TWO_CENTRAL_FACTORY

#include "Tile.h"

#include <vector>

class CentralFactory {
public:
    CentralFactory();
    ~CentralFactory();

    /**
    * Get a tile at the index of the factory
    */
    Tile* getTile(int index);

    /**
    * Add a tile to the end of the factory
    */
    void add(Tile* tile);

    /**
    * Remove a Tile from the index of the factory
    */
    void remove(int index);

    /**
    * Print all tiles in factories letters
    */
    void printletters();

    /**
    * Return vector size
    */
    int size();

    /**
    * Remove back of vector
    */
    void removeBack();

private:
/** This is our chosen vector, since the central factory never has a set amount of tiles we
* believed this was the perfect selection.
*/
std::vector<Tile*> Tiles;
} ;

#endif //COSC_ASSIGN_TWO_FACTORY