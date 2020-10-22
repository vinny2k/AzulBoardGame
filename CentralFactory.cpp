#include "CentralFactory.h"

CentralFactory::CentralFactory() {
}
// Deconstructor loops through the vector removing the last item
CentralFactory::~CentralFactory(){
    while(Tiles.size() != 0){
        Tiles.pop_back();
    }
}

Tile* CentralFactory::getTile(int index){
    return Tiles[index];
}
// New tile added to back of vector
void CentralFactory::add(Tile* tile){
    Tile* newTile = new Tile(*tile);
    Tiles.push_back(newTile);
}
// Goes to front of vector then reaches the index and deletes it
void CentralFactory::remove(int index){
    Tiles.erase(Tiles.begin() + index);
}
// Prints all letters of all the tiles in central factory
void CentralFactory::printletters(){
    for(unsigned int i = 0;  i < Tiles.size(); i++){
        Tiles.at(i)->printLetter();
    }
}

int CentralFactory::size(){
    return Tiles.size();
}

void CentralFactory::removeBack(){
    Tiles.pop_back();
}