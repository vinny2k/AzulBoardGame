#include "BoxLid.h"

BoxLid::BoxLid() {
}

BoxLid::~BoxLid() {
    // while the boxlid is not empty
    while (boxlid.size() != 0) {
        // remove the last tile from the boxlid
        boxlid.pop_back();
    }
}

void BoxLid::add(Tile* tile) {
    // add given tile to back of the box lid
    boxlid.push_back(tile);
}

Tile* BoxLid::get(int i) {
    // return a tile from box lid at given index
    return boxlid.at(i);
}

int BoxLid::size() {
    // return size of the box lid
    return boxlid.size();
}

LinkedList* BoxLid::refillTileBag(LinkedList* tileBag) {
    // while the box lid is not empty
    while (boxlid.size() != 0) {
        // add copy of the front tile of box lid to the tilebag
        tileBag->addBack(new Tile(*boxlid.front()));
        // remove the front tile from the box lid
        boxlid.pop_front();
    }

    // return the tile bag
    return tileBag;
}