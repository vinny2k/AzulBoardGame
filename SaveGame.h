#ifndef COSC_ASSIGN_SG
#define COSC_ASSIGN_SG

#include <iostream>
#include <stdexcept>
#include <vector>

class SaveGame {
public:
    SaveGame();
    ~SaveGame();

    /**
    * Get a move at the index of the moves vector
    */
    std::string getMove(int index);

    /**
    * Add a move to the end of the vector
    */
    void add(std::string move);

    /**
    * Remove a move from an index of the vector
    */
    void remove(int index);

    /**
    * return the size of the vector
    */
    int size();

    /**
    * Changes the inital tilebag
    */
    void changeInital(std::string tb);

    /**
    * Returns the inital tilebag
    */
    std::string returnInital();

private:
    std::vector<std::string> moves;
    std::string inital;
} ;

#endif //COSC_ASSIGN_SG