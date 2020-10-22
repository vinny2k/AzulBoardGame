#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(Colour colour)
{
   this->colour = colour;
}

Tile::Tile(Tile& other) {
   this->colour = other.colour;
}

Tile::~Tile() {
}

void Tile::setColour(Colour colour){
   this->colour = colour;
}

Colour Tile::getColour() {
   return colour;
}

std::string Tile::getletter(){
   Colour colour = getColour();
   std::string returnval;
   if(colour == 0){
      returnval =  "R";
   } else if (colour == 1){
      returnval = "Y";
   } else if (colour == 2){
      returnval = "B";
   } else if (colour == 3){
      returnval = "L";
   } else if (colour == 4){
      returnval = "U";
   } else if (colour == 5){
      returnval = "F";
   } else if (colour == 6){
      returnval = ".";
   } else if (colour == 7){
      returnval = " ";
   }
   return returnval;
}

void Tile::printLetter() {
   if(colour == 0){
      std::cout << "R ";
   } else if (colour == 1){
      std::cout << "Y ";
   } else if (colour == 2){
      std::cout << "B ";
   } else if (colour == 3){
      std::cout << "L ";
   } else if (colour == 4){
      std::cout << "U ";
   } else if (colour == 5){
      std::cout << "F ";
   } else if (colour == 6){
      std::cout << ". ";
   } else if (colour == 7){
      std::cout << "  ";
   } else{
      std::cout << "  ";
   }
}

bool Tile::isColoured() {
   return colour != Blank && colour != No_Tile;
}