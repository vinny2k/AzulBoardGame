#include "Player.h"

Player::Player(std::string name, int points) :
    name(name),
    points(points)
    {
    this->mosaic = new Mosaic();
    this->first = false;
}

Player::~Player() {
    delete mosaic;
}

Mosaic* Player::getMosaic() {
    return mosaic;
}

std::string Player::getName() {
    return name;
}

int Player::getPoints() {
    return points;
}

void Player::setPoints(int points) {
    this->points = points;
}

void Player::setFirst(bool first){
    this->first = first;
}

bool Player::getFirst(){
    return first;
}

void Player::changeName(std::string newname){
    this->name = newname;
}