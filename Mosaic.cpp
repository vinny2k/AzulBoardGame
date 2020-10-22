#include "Mosaic.h"

Mosaic::Mosaic()
{

    // initialising storage
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            storage[i][j] = new Tile(Blank);
        }
        for (int j = STORAGE_ARRAY_INDEX; j > 3 - i; --j)
        {
            storage[i][j] = new Tile(No_Tile);
        }
    }

    // initialising grid
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            grid[i][j] = new Tile(No_Tile);
        }
    }

    // initialising broken
    for (int i = 0; i < BROKEN_SIZE; ++i)
    {
        broken[i] = new Tile(Blank);
    }

    // initialising storageRowIsFull array
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        storageRowIsFull[i] = false;
    }

    // initialising storageRowColour array
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        storageRowColour[i] = No_Tile;
    }
}

Mosaic::~Mosaic()
{   
    // Goes through all arrays and deletes tiles
    for (int i = 0; i < BROKEN_SIZE; ++i)
    {   
        delete broken[i];
        broken[i] = nullptr;
    }
    
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            delete grid[i][j];
            grid[i][j] = nullptr;
        }
    }

    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            delete storage[i][j];
            storage[i][j] = nullptr;
        }
    }
}

void Mosaic::print()
{
    // Goes through all arrays and prints
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {

        std::cout << i + 1 << ": ";

        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            storage[i][j]->printLetter();
            std::cout << ' ';
        }

        std::cout << "|| ";

        for (int j = 0; j < ROW_COL_SIZE; ++j)
        {
            grid[i][j]->printLetter();
            std::cout << ' ';
        }

        std::cout << std::endl;
    }

    std::cout << "broken: ";

    for (int i = 0; (unsigned)i < BROKEN_SIZE; ++i)
    {
        broken[i]->printLetter();
        std::cout << ' ';
    }

    std::cout << std::endl;
}

void Mosaic::setStorageRow(Tile *tile, int rowIndex, int numTiles)
{
    // Chosen tile is set in the array 
    for (int i = 0; i < numTiles; ++i)
    {
        // New tile createdthis is to prevent issue in moving of tiles to broken array
        Tile *ntile = new Tile(*tile); 
        storage[rowIndex - 1][STORAGE_ARRAY_INDEX - i] = ntile;
    }
}
// Overloaded function
void Mosaic::setStorageRow(Tile *tile, int rowIndex, int numTiles, int startIndex)
{
    // This method sets a starting point, if tile is already in row
    for (int i = startIndex; i > 0 + startIndex - numTiles; --i)
    {
        Tile *ntile = new Tile(*tile); //this is to prevent issue in moving of tiles to broken array
        storage[rowIndex - 1][i] = ntile;
    }
}

Tile *Mosaic::getStorageRowTile(int rowIndex)
{
    Tile *tempTile = nullptr;
    int count = 0;
    // loops through the storage row of given index and instantiates tempTile as a new tile of given colour
    for (int i = 0; i < rowIndex + 1; ++i)
    {
        if (storage[rowIndex][i]->getColour() != Blank && storage[rowIndex][i]->getColour() != No_Tile)
        {
            tempTile = new Tile(storage[rowIndex][i]->getColour());
            ++count;
        }
    }
    return tempTile;
}

Tile *Mosaic::getStorageTile(int row, int column){
    return storage[row][column];
}

void Mosaic::getBrokenTile(int rowIndex, BoxLid* boxlid)
{
    Tile *tile = nullptr;
    int nonBroken = rowIndex + 1;
    int brokenIndex = 0;
    //Goes through broken and returns tile at certain index
    for (int i = STORAGE_ARRAY_INDEX; i >= 0; --i)
    {
        if (storage[rowIndex][i]->getColour() != Blank && storage[rowIndex][i]->getColour() != No_Tile && 5 - i > nonBroken)
        {
            tile = new Tile(storage[rowIndex][i]->getColour());
            storage[rowIndex][i]->setColour(Blank);
            if(Brokensize() == BROKEN_SIZE) {
                    boxlid->add(tile);
            } else {
                while (broken[brokenIndex]->getColour() != Blank){
                    brokenIndex++;
                }
                broken[brokenIndex] = tile;
            }
        }
    }
}

void Mosaic::clearStorageRow(int rowIndex)
{
    Tile *clear[ROW_COL_SIZE] = {};
    // goes through storages and sets tiles to blank
    for (int i = 0; i <= ROW_COL_SIZE - rowIndex; ++i)
    {
        clear[i] = new Tile[Blank];
        std::cout << clear[i]->getColour() << std::endl;
    }

    for (int i = 0; i <= rowIndex; ++i)
    {
        std::cout << i << std::endl;
        clear[STORAGE_ARRAY_INDEX - i] = new Tile(No_Tile);
    }

    // setting the storage row with clear array
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        storage[rowIndex][i] = clear[i];
        std::cout << clear[i]->getColour() << std::endl;
    }
}

void Mosaic::setGridRow(Tile *tile, int rowIndex)
{
    // Sets a specific grid row
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        if (gridTemplate[rowIndex][i] == tile->getColour())
        {
            grid[rowIndex][i] = new Tile(*tile);
        }
    }
}

void Mosaic::setBroken(Tile *temp, int i)
{
    // Sets broken
    int tempIndex = 0;
    for (int j = 0; j < i + 1; ++j)
    {

        // checks if the current index is not empty
        if (broken[tempIndex]->getColour() != Blank)
        {

            // if not empty, increment both j and i
            ++j;
            ++i;
        }
        else
        {

            // else set the current index with the temp tile
            broken[tempIndex] = new Tile(*temp);
            ++tempIndex;
        }
    }
}

void Mosaic::addBroken(Tile* temp, BoxLid* boxlid){
    // Adds tile to back of broken
    int count = 0;
    for(int i = 0; i < BROKEN_SIZE; i++){
        if(broken[i]->isColoured()){
            count++;
        }
    }
    // If broken full the tile is added to the back of the box lid
    if(count == BROKEN_SIZE){
        boxlid->add(new Tile(*temp));
    } else{
        broken[count] = new Tile(*temp);
    }
}

bool Mosaic::checkfirst() {
    // Checks if the first tile is in the broken array
    bool first = false;
    for (int h = 0; h < BROKEN_SIZE; h++){
        if(broken[h]->getColour() == First_Player){
            first = true;
        }
    }
    // If so true is returned
    return first;
}

BoxLid* Mosaic::clearBroken(BoxLid* boxlid){
    // Clears the broken line
    for (int h = 0; h < BROKEN_SIZE; h++){
        if(broken[h]->getColour() != First_Player && broken[h]->getColour() != Blank){
            boxlid->add(new Tile(*broken[h]));
        }
    }

    for (int h = 0; h < BROKEN_SIZE; ++h){
        broken[h] = new Tile(Blank);
    }
    std::cout << std::endl;
    return boxlid;
}

std::string Mosaic::checkrowcolour(int rowIndex)
{
    return storage[rowIndex - 1][STORAGE_ARRAY_INDEX]->getletter();
}

BoxLid* Mosaic::endOfRound(BoxLid* boxlid)
{
    int lastTileSpace = 0;
    Colour currentColour = Blank;

    // for each row of storage
    for (int i = 0; i < ROW_COL_SIZE; ++i)
    {
        lastTileSpace = STORAGE_ARRAY_INDEX - i;

        currentColour = storage[i][lastTileSpace]->getColour();

        if (currentColour != Blank)
        {
            //for each index in row of grid template
            for (int j = 0; j < ROW_COL_SIZE; j++)
            {
                if (currentColour == gridTemplate[i][j])
                {
                    Tile *tile = new Tile(currentColour);
                    grid[i][j] = tile;
                }
            }
            //copying coloured tiles into tilebag, not including the right-most tile
            for (int k = 0; k < STORAGE_ARRAY_INDEX; ++k){
                if (storage[i][k]->getColour() == currentColour && storage[i][k]->isColoured())
                {
                    boxlid->add(new Tile(*storage[i][k]));
                }
            }

            //for each index of storage
            for (int k = 0; k < ROW_COL_SIZE; ++k){
                if (storage[i][k]->getColour() == currentColour)
                {
                    Tile *tile = new Tile(No_Tile);
                    storage[i][k] = tile;
                }
            }
        }
    }
    return boxlid;
}

void Mosaic::checkIfStorageIsFull(){
    int rowNo = 0; // storage row number
    int count = 0; // count of coloured tiles in a row
    // looping for all 5 storage rows
    while (rowNo < ROW_COL_SIZE) {
        // looping for all 5 storage columns
        for (int i = STORAGE_ARRAY_INDEX; i >= 0; --i) {
            // increments count if the tile is not blank, no_tile or a first_player tile
            if (storage[rowNo][i]->isColoured()) {
                ++count;
            }
        }
        // sets storageRowIsFull index to true if all tiles are coloured in storage row, where index corresponds to row number
        if (count == rowNo + 1) {
            storageRowIsFull[rowNo] = true;
        }
        // sets storageRowColour index to colour of the right-most tile of the storage row, where index corresponds to row number
        // resets count to 0 for the next row
        // increments rowNo to move to the next row
        storageRowColour[rowNo] = storage[rowNo][STORAGE_ARRAY_INDEX]->getColour();
        count = 0;
        ++rowNo;
    }
}

bool Mosaic::returnIfStorageIsFull(int row){
    bool returnval = false;
    int count = 0; // count of coloured tiles in a row
    // looping for all 5 storage rows
    if(row != 6){
        for (int i = 0; i < ROW_COL_SIZE; ++i) {
            // increments count if the tile is not blank, no_tile or a first_player tile
            if (storage[row-1][i]->isColoured()) {
                ++count;
            }
        }
        // sets storageRowIsFull index to true if all tiles are coloured in storage row, where index corresponds to row number
        if (count == row) {
            returnval = true;
        }
    } else {
        returnval = false;
    }
    return returnval;
}

int Mosaic::scoring(int score, int roundCount) {
    // player score to be returned
    int newScore = score;

    // int to check if score has been incremented for horizontally linked tiles
    int jScore = 0;
    // int to check if score has been incremented for vertically linked tiles
    int iScore = 0;
    
    // offset for checking for horizontally linked tiles
    int jOffset = 1; 
    // offset for checking for vertically linked tiles
    int iOffset = 1; 
    // bool value used as while loop condition when checking horizontal and vertically
    bool canContinue = true;  
    
    // looping for each grid row
    for (int i = 0; i < ROW_COL_SIZE; ++i) {
        // if the respective storage row was full
        if (storageRowIsFull[i] == true) {
            // find the new tile, set x and y to respective values, increment score
            for (int j = 0; j < ROW_COL_SIZE; j++) {
                if (grid[i][j]->getColour() == storageRowColour[i] && grid[i][j]->isColoured()) {
                    ++newScore;
                    // loop to find horizontal linked tiles on left side, increment for each linked to tile
                    while (canContinue) {
                        if (j - jOffset >= 0 && grid[i][j - jOffset]->isColoured()) {
                            ++newScore;
                            ++jScore;
                            ++jOffset;
                        } else {
                            canContinue = false;
                        }
                    }
                    // resetting jOffset value to 1
                    jOffset = 1; 
                    // resetting bool value for next while loop
                    canContinue = true; 

                    // loop to find horizontal linked tiles on right side, increment for each linked to tile
                    while (canContinue) {
                        if (j + jOffset <= STORAGE_ARRAY_INDEX && grid[i][j + jOffset]->isColoured()) {
                            ++newScore;
                            ++jScore;
                            ++jOffset;
                        } else {
                            canContinue = false;
                        }
                    }
                    // resetting jOffset value to 1
                    jOffset = 1; 
                    canContinue = true; // resetting bool value for next while loop

                    // loop to find vertical linked tiles on top side, increment for each linked to tile
                    while (canContinue) {
                        if (i - iOffset >= 0 && grid[i - iOffset][j]->isColoured()) {
                            ++newScore;
                            ++iScore;
                            ++iOffset;
                        } else {
                            canContinue = false;
                        }
                    }
                    // resetting iOffset value to 1
                    iOffset = 1; 
                     // resetting bool value for next while loop
                    canContinue = true;
                    // loop to find vertical linked tiles on bottom side, increment for each linked to tile
                    while (canContinue) {
                        if (i + iOffset <= STORAGE_ARRAY_INDEX && grid[i + iOffset][j]->isColoured()) {
                            ++newScore;
                            ++iScore;
                            ++iOffset;
                        } else {
                            canContinue = false;
                        }
                    }
                    // if score has been incremented for horizontally and vertically linked tiles, increment score
                    if (jScore > 0 && iScore > 0) {
                        ++newScore;
                    }
                    jScore = 0;
                    iScore = 0;
                    // resetting iOffset value to 1
                    iOffset = 1; 
                     // resetting bool value for next while loop
                    canContinue = true;
                }                
            }
        }
    }

    // looping for the broken tiles
    for (int i = 0; i < BROKEN_SIZE; ++i) {
        if ((i == 0 || i == 1) && broken[i]->isColoured()) {
            --newScore;
        } else if ((i == 2 || i == 3 || i == 4) && broken[i]->isColoured()) {
            newScore -=2;
        } else if ((i == 5 || i == 6) && broken[i]->isColoured()) {
            newScore -=3;
        }
    }
    return newScore;
}

bool Mosaic::alreadyThere(int rowindex, std::string tilecol){
    // Checks if a tile is already in the grid
    bool returnval = false;
    if(rowindex != 6){
        for(int i = 0; i<ROW_COL_SIZE; i++){
            if(grid[rowindex-1][i]->getletter() == tilecol){
                returnval = true;
            }
        }
    } else {
        returnval = false;
    }
    return returnval;
}

void Mosaic::checkForBroken( BoxLid* boxlid)
{
    for (int i = 0; i < BROKEN_SIZE; ++i)
    {
        getBrokenTile(i, boxlid);
    }
}
int Mosaic::Brokensize(){
    int count = 0;
    for(int i = 0; i < BROKEN_SIZE; i++){
        if(broken[i] != nullptr && broken[i]->getColour() != Blank){
            count++;
        }
    }
    return count;
}