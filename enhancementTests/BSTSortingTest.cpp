#include "../BSTFactory.h"

int main (void) {

    BSTFactory* bstFactory = new BSTFactory();

    std::cout << "created bstFactory" << std::endl;

    bstFactory->add(new Tile(Dark_Blue));
    std::cout << "added darkblue tile" << std::endl;

    bstFactory->add(new Tile(Red));
    std::cout << "added red tile" << std::endl;

    bstFactory->add(new Tile(Light_Blue));
    std::cout << "added light blue tile" << std::endl; 

    bstFactory->add(new Tile(Black));
    std::cout << "added black tile" << std::endl;

    bstFactory->add(new Tile(Yellow));
    std::cout << "added yellow tile" << std::endl;

    bstFactory->printletters();
}