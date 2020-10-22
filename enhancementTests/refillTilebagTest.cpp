#include <iostream>

#include "../BoxLid.h"
#include "../LinkedList.h"

int main (void) {

    BoxLid* boxlid = new BoxLid();

    LinkedList* tilebag = new LinkedList();

    for (int i = 0; i < 20; i++)
    {
        Tile *tile_red = new Tile(Red);
        boxlid->add(tile_red);
        Tile *tile_db = new Tile(Dark_Blue);
        boxlid->add(tile_db);
        Tile *tile_yellow = new Tile(Yellow);
        boxlid->add(tile_yellow);
        Tile *tile_lb = new Tile(Light_Blue);
        boxlid->add(tile_lb);
        Tile *tile_black = new Tile(Black);
        boxlid->add(tile_black);
    }

    boxlid->refillTileBag(tilebag);

    std::cout << "Tiles in box lid: ";

    for (int i = 0; i < boxlid->size(); ++i) {
        std::cout << boxlid->get(i)->getletter();
    }
    std::cout << std::endl;

    std::cout << "Tiles in tile bag: " << tilebag->getTilesAsString() << std::endl;

    return EXIT_SUCCESS;
}