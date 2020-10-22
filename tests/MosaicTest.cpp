#include "../Mosaic.h"

#include <iostream>

void Mtest() {
    std::cout << "Beginning test . . ." << std::endl;
    std::cout << "... creating mosaic ..." << std::endl;
    Mosaic* mosaic = new Mosaic();

    std::cout << "... testing print method ..." << std::endl;
    mosaic->print();
    
    std::cout << "... testing setter method for the broken tiles array ..." << std::endl;
    int j = 1;
    Tile* newBroken[j] = {new Tile(Yellow)};    
    mosaic->setBroken(newBroken, j);

    std::cout << "... printing updated mosaic ..." << std::endl;
    mosaic->print();

    std::cout << "... testing setter method for storage array ..." << std::endl;
    int k = 2;
    int storageRow = 3;
    Tile* newStorage[2] = {new Tile(Red), new Tile(Red)};
    mosaic->setStorageRow(newStorage, storageRow, k);

    std::cout << "... printing updated mosaic ..." << std::endl;
    mosaic->print(); 

    std::cout << "... testing setter method for grid array (the setter method will be updated to reflect the grid pattern)..." << std::endl;
    mosaic->setGridRow(mosaic->getStorageRowTile(3), 3);
    mosaic->clearStorageRow(3);

    std::cout << "... printing updated mosaic ..." << std::endl;
    mosaic->print();

    std::cout << " . . . Ending test" << std::endl;

    delete mosaic;
}