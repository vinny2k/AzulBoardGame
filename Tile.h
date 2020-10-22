#ifndef COSC_ASSIGN_TWO_TILE
#define COSC_ASSIGN_TWO_TILE

#include <iostream>
// Creating enumaration for tile colours
enum Colour {
    Red, //= 'R'
    Yellow, // = 'Y'
    Dark_Blue, // = 'B'
    Light_Blue, // = 'L'
    Black, // = 'U'
    First_Player, // = 'F'
    No_Tile, // = '.'
    Blank, // = ' '
} ;
// Creating class for tiles
class Tile {
public:
    Tile();
    Tile(Colour colour);
    Tile(Tile& other);
    ~Tile();
    /**
    * Sets the colour of the tile
    */
    void setColour(Colour colour);
    /**
    * Get the colour of the tile
    */
    Colour getColour();
    /**
    * Get the letter of the tile
    */
    std::string getletter();
    /**
    * Prints the letter of the tile
    */
    void printLetter();
    /**
    * Returns bool based on if colour isn't blank or a no tile
    */
    bool isColoured();

private:
    Colour colour;
} ;

#endif //COSC_ASSIGN_TWO_TILE