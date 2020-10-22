#ifndef BOXLID_H
#define BOXLID_H

#include "Tile.h"
#include "LinkedList.h"
#include <deque>

/**
* Enhancement class representing the Box Lid with as a deque
*/
class BoxLid {
public:
    BoxLid();
    ~BoxLid();

    /**
    * adds given tile into the boxlid
    */ 
    void add(Tile* tile);

    /**
    * adds given tile into the boxlid
    */ 
    Tile* get(int i);

    /**
    * returns size of boxlid
    */ 
    int size();

    /**
    * refills the given tilebag with tiles from boxlid
    */ 
    LinkedList* refillTileBag(LinkedList* tileBag);

private:
    std::deque<Tile*> boxlid;
};
#endif // BOXLID_H