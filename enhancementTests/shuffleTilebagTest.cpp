#include "../LinkedList.h"
#include <iostream>

int main (void) {
    LinkedList* tilebag = new LinkedList();
    

    for (int i = 0; i < 20; i++)
    {
        Tile *tile_red = new Tile(Red);
        tilebag->addBack(tile_red);
        Tile *tile_db = new Tile(Dark_Blue);
        tilebag->addBack(tile_db);
        Tile *tile_yellow = new Tile(Yellow);
        tilebag->addBack(tile_yellow);
        Tile *tile_lb = new Tile(Light_Blue);
        tilebag->addBack(tile_lb);
        Tile *tile_black = new Tile(Black);
        tilebag->addBack(tile_black);
    }

    int seed = 0;

    std::cout << "enter seed" << std::endl;

    std::cin >> seed;

    tilebag->shuffle(seed);

    std::cout << tilebag->getTilesAsString() << std::endl;

    return EXIT_SUCCESS;
}