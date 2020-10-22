#ifndef COSC_ASSIGN_TWO_MOSAIC
#define COSC_ASSIGN_TWO_MOSAIC

#include "Tile.h"
#include "BoxLid.h"

#include <iostream>

#define ROW_COL_SIZE 5
#define ROUNDS 5
#define BROKEN_SIZE 7
#define STORAGE_ARRAY_INDEX 4

class Mosaic {
public:
    Mosaic();
    ~Mosaic();

    /**
    * Prints mosaic 
    */
    void print();
    /**
    * Sets storage row 
    */
    void setStorageRow(Tile* tile, int rowIndex, int numTiles);
    /**
    * Sets storage row 
    */
    void setStorageRow(Tile *tile, int rowIndex, int numTiles, int startIndex);
    /**
    * Gets storage row tile
    */
    Tile* getStorageRowTile(int rowIndex);
    /**
    * Get storage row tile in specific spot
    */
    Tile* getStorageTile(int row, int column);
    /**
    * Gets broken tile and moves it to storage
    */
    void getBrokenTile(int rowIndex, BoxLid* boxlid);
    /**
    * Clears storage row
    */
    void clearStorageRow(int rowIndex);
    /**
    * Sets grid tile
    */
    void setGridRow(Tile* tile, int rowIndex);
    /**
    * Sets broken tile
    */
    void setBroken(Tile* temp, int numTiles);
    /**
    * Adds tile to back of the broken line, if full goes to box lid
    */
    void addBroken(Tile* temp, BoxLid* boxlid);
    /**
    * Checks if first tile is in broken
    */
    bool checkfirst();
    /**
    * Clears broken row
    */
    BoxLid* clearBroken(BoxLid* boxlid);
    /**
    * Returns row colour
    */
    std::string checkrowcolour(int rowIndex);
    /**
    * Moves tiles according to end of round rules
    */
    BoxLid* endOfRound(BoxLid* boxlid);
    /**
    * Will check if storage is full
    */
    void checkIfStorageIsFull();
    /**
    * Will return a boolean value if storage is full
    */
    bool returnIfStorageIsFull(int row);
    /**
    * Gets scoring for end of round
    */
    int scoring(int score, int roundCount);
    /**
    * Returns true if tile is already in grid
    */
    bool alreadyThere(int rowindex, std::string tilecol);
    /**
    * Checks for broken tiles needing to be moved
    */
    void checkForBroken(BoxLid* boxlid);
    /**
    * Returns size of broken
    */
    int Brokensize();

private:
    // Left side of mosaci
    Tile* storage[ROW_COL_SIZE][ROW_COL_SIZE];
    // Right side
    Tile* grid[ROW_COL_SIZE][ROW_COL_SIZE];
    // Broken line
    Tile* broken[BROKEN_SIZE];

    bool storageRowIsFull[ROW_COL_SIZE];
    Colour storageRowColour[ROW_COL_SIZE];

    // template mosaic grid for moving tiles from storage to grid
    Colour gridTemplate[ROW_COL_SIZE][ROW_COL_SIZE] = {
        {Dark_Blue, Yellow, Red, Black, Light_Blue},
        {Light_Blue, Dark_Blue, Yellow, Red, Black}, 
        {Black, Light_Blue, Dark_Blue, Yellow, Red}, 
        {Red, Black, Light_Blue, Dark_Blue, Yellow}, 
        {Yellow, Red, Black, Light_Blue, Dark_Blue}
    };
};

#endif // COSC_ASSIGN_TWO_MOSAIC