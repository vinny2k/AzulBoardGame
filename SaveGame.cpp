#include "SaveGame.h"

SaveGame::SaveGame() {
}

SaveGame::~SaveGame(){
    while(moves.size() != 0){
        moves.pop_back();
    }
}

std::string SaveGame::getMove(int index){
    return moves[index];
}

void SaveGame::add(std::string move){
    moves.push_back(move);
}

void SaveGame::remove(int index){
    moves.erase(moves.begin() + index);
}

int SaveGame::size(){
    return moves.size();
}

void SaveGame::changeInital(std::string tb){
    this->inital = tb;
}

std::string SaveGame::returnInital(){
    return inital;
}
