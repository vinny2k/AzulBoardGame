#include <iostream>

#include "../Factory.h"

void Ftest(){
    std::cout << "Beginning test . . ." << std::endl;

    std::cout << "... creating factory ..." << std::endl;
    Factory* factory = new Factory();

    std::cout << "... creating tiles ..." << std::endl;
    std::cout << "... red, yellow, dark blue and light blue ..." << std::endl;
    Tile* tile0 = new Tile(Red);
    Tile* tile1 = new Tile(Yellow);
    Tile* tile2 = new Tile(Dark_Blue);
    Tile* tile3 = new Tile(Light_Blue);

    std::cout << "... adding tiles to factory ..." << std::endl;
    factory->add(tile0, 0);
    factory->add(tile1, 1);
    factory->add(tile2, 2);
    factory->add(tile3, 3);

    std::cout << "... getting tiles from factory - should be: R, Y, B, L ..." << std::endl;
    std::cout << "... first tile = ";
    factory->getTile(0)->printLetter();
    std::cout << " ..." << std::endl << "... second tile = ";
    factory->getTile(1)->printLetter();
    std::cout << " ..." << std::endl << "... third tile = ";
    factory->getTile(2)->printLetter();
    std::cout << " ..." << std::endl << "... fourth tile = ";
    factory->getTile(3)->printLetter();
    std::cout << " ..." << std::endl;

    std::cout << "... copying factory ..." << std::endl;
    Factory* factoryCopy = new Factory(*factory);

    std::cout << "... getting tiles from factory copy - should be: R, Y, B, L ..." << std::endl;
    std::cout << "... first tile = ";
    factoryCopy->getTile(0)->printLetter();
    std::cout << " ..." << std::endl << "... second tile = ";
    factoryCopy->getTile(1)->printLetter();
    std::cout << " ..." << std::endl << "... third tile = ";
    factoryCopy->getTile(2)->printLetter();
    std::cout << " ..." << std::endl << "... fourth tile = ";
    factoryCopy->getTile(3)->printLetter();
    std::cout << " ..." << std::endl;

    std::cout << ". . . Ending test" << std::endl;

    delete factoryCopy;
    delete factory;
}