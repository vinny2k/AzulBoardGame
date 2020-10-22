#ifndef COSC_ASSIGN_TWO_PLAYER
#define COSC_ASSIGN_TWO_PLAYER

#include <iostream>

#include "Mosaic.h"

class Player {
public:
    Player(std::string name, int points);
    ~Player();

    Mosaic* getMosaic();

    std::string getName();

    int getPoints();
    void setPoints(int points);
    bool getFirst();
    void setFirst(bool first);
    void changeName(std::string newname);
    
private:
    Mosaic* mosaic;
    std::string name;
    int points;
    bool first;
};
#endif // COSC_ASSIGN_TWO_PLAYER