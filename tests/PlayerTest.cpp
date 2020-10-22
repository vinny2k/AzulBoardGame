#include <iostream>

#include "../Player.h"

void Ptest() {
    std::cout << "Beginning test . . ." << std::endl;
    std::cout << "... creating player ..." << std::endl;
    Player* player = new Player("Jia", 0);

    std::cout << "... printing players mosaic ..." << std::endl;
    player->getMosaic()->print();

    std::cout << "... printing players information ..." << std::endl;
    std::cout << "Player name is: " << player->getName()  << ", player points is: " << player->getPoints() << std::endl;

    std::cout << "... Changing players points (Should be 10) ..." << std::endl;
    player->setPoints(10);
    std::cout << "Player name is: " << player->getName()  << ", player points is: " << player->getPoints() << std::endl;

    std::cout << ". . . Ending test" << std::endl;

    delete player;
}