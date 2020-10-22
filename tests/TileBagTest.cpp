#include <iostream>

#include "../LinkedList.h"

void TBtest() {
    std::cout << "Beginning test . . ." << std::endl;
    std::cout << "... creating factory ..." << std::endl;
    LinkedList* tilebag = new LinkedList();

    std::cout << "... creating tiles ..." << std::endl;
    std::cout << "... red, dark blue, yellow, black and light blue ..." << std::endl;
    Tile* nt = new Tile(Red);
    Tile* nt1 = new Tile(Dark_Blue);
    Tile* nt2 = new Tile(Yellow);
    Tile* nt3 = new Tile(Black);
    Tile* nt4 = new Tile(Light_Blue);

    std::cout << "... adding red and dark blue to front ..." << std::endl;    
    tilebag->addFront(nt);
    tilebag->addFront(nt1);
    std::cout << "... adding other three tiles to end ..." << std::endl;    
    tilebag->addBack(nt2);
    tilebag->addBack(nt3);
    tilebag->addBack(nt4);

    std::cout << "... getting size (shoudl be 5) ..." << std::endl;    
    std::cout << tilebag->size() << std::endl;
    std::cout << "... getting index 1 (shoudl be red) ..." << std::endl;    
    tilebag->get(1)->printLetter();

    std::cout << std::endl << "... removing one item from front and back of list ..." << std::endl;    
    tilebag->removeBack();
    tilebag->removeFront();

    std::cout << "... getting new size (should be 3) ..." << std::endl;    
    std::cout << tilebag->size() << std::endl;
    std::cout << "... getting new index one (should be yellow) ..." << std::endl;    
    tilebag->get(1)->printLetter();
    std::cout << std::endl << "... clearing list and checking size (should be 0) ..." << std::endl;    
    tilebag->clear();
    std::cout << tilebag->size() << std::endl;

    std::cout << " . . . Ending test" << std::endl;

    delete tilebag;
}