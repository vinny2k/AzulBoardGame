#include "LoadGame.h"
// Creating new objects at start of game
LoadGame::LoadGame() {
    this->lg_player1 = new Player("no name", ROUND_START);
    this->lg_player2 = new Player("no name1", ROUND_START);
    this->lg_factory1 = new BSTFactory();
    this->lg_factory2 = new BSTFactory();
    this->lg_factory3 = new BSTFactory();
    this->lg_factory4 = new BSTFactory();
    this->lg_factory5 = new BSTFactory();
    this->lg_centralfactory = new CentralFactory();
    this->lg_tilebag = new LinkedList();
    this->lg_boxlid = new BoxLid();
    this->lg_savegame = new SaveGame();
    this->lg_roundCount = ROUND_START;
}
// Deconstructor removes all moves from vector and all other objects
LoadGame::~LoadGame(){
    while(loadedmoves.size() != 0){
        loadedmoves.pop_back();
    }
    delete lg_player1;
    delete lg_player2;
    delete lg_factory1;
    delete lg_factory2;
    delete lg_factory3;
    delete lg_factory4;
    delete lg_factory5;
    delete lg_centralfactory;
    delete lg_tilebag;
    delete lg_boxlid;
    delete lg_savegame;
}

void LoadGame::readfile(std::string filename){
    std::string line;
    std::ifstream loadfile;
    loadfile.open(filename);
    // Files is opened and looped through untill end of file is reached
    while(!loadfile.eof()){
	        std::getline(loadfile,line);
            // Line is added to the back of the moves vector 
	        loadedmoves.push_back(line);
        }
	loadfile.close();
}

int LoadGame::size(){
    // Returns the size of the moves vector
    return loadedmoves.size();
}

void LoadGame::setup(){
    // Goes through the inital tile bag and adds to tile bag
    for(int i = 0; (unsigned) i<loadedmoves[0].length(); i++){
        // If letter corresponds to colour then new tile is created and added to the back of the tilebag
        if(loadedmoves[0].substr(i,1) == "R"){
            Tile* tile_red = new Tile(Red);
            lg_tilebag->addBack(tile_red);
        } else if(loadedmoves[0].substr(i,1) == "L"){
            Tile* tile_LB = new Tile(Light_Blue);
            lg_tilebag->addBack(tile_LB);
        } else if(loadedmoves[0].substr(i,1) == "U"){
            Tile* tile_Black = new Tile(Black);
            lg_tilebag->addBack(tile_Black);
        } else if(loadedmoves[0].substr(i,1) == "B"){
            Tile* tile_DB = new Tile(Dark_Blue);
            lg_tilebag->addBack(tile_DB);
        } else if (loadedmoves[0].substr(i,1) == "Y"){
            Tile* tile_Yellow = new Tile(Yellow);
            lg_tilebag->addBack(tile_Yellow);
        }
    } 
    // Inital tile bag is set
    lg_savegame->changeInital(loadedmoves[0]);
    // Players names are set from file
    lg_player1->changeName(loadedmoves[1]);
    lg_player2->changeName(loadedmoves[2]);
    // Player 1 goes first
    lg_player1->setFirst(true);
}
// This method goes through all turns made and makes them
void LoadGame::round(bool test)
{   
    // Factories are set up
    factorySetUp();
    bool round_start = true;
    int turn = 0;
    // First player gets the first turn
    if(lg_player1->getFirst() == true){
        turn = 1;
    } else {
        turn = 2;
    }
    // This for loop goes through all moves and makes them
    for(int i = 3; (unsigned) i < loadedmoves.size(); i++){
        // If there is a blank line then it is ignored
        if(loadedmoves[i].substr(START_INPUT, 5) != ""){
            // If rounds not over a move is made
            if(roundover() == false){
                // If player ones first and the rounds just started
                if(lg_player1->getFirst() == true && round_start == true){
                    move(lg_player1, loadedmoves[i]);
                    lg_savegame->add(loadedmoves[i]);
                    round_start = false;
                    turn = 2;
                // If players two first and the rounds just started
                } else if(lg_player2->getFirst() == true && round_start == true){
                    move(lg_player2, loadedmoves[i]);
                    lg_savegame->add(loadedmoves[i]);
                    round_start = false;
                    turn = 1;
                // If its not start of round then whoevers turn it is goes
                } else if (turn == 1){
                    // Move is called
                    move(lg_player1, loadedmoves[i]);
                    // Move is saved so if the game is saved again after its loaded the original moves are still saved
                    lg_savegame->add(loadedmoves[i]);
                    // Turn is then player two's
                    turn = 2;
                } else if (turn == 2){
                    move(lg_player2, loadedmoves[i]);
                    lg_savegame->add(loadedmoves[i]);
                    // Turn is now player ones
                    turn = 1;
                }
            // If the rounds ended
            } else {
                //Round end function is called
                roundend();
                // Start of round is set to true
                round_start = true;
                // Whoever has first tile goes first next round
                if(lg_player1->getFirst() == true){
                    turn = 1;
                } else {
                    turn = 2;
                }
                // Making sure this doesn't count as a turn
                i = i -1;
            }
        } 
        // This is for when the last move of the save file ends the round
        if(roundover() == true){
            roundend();
            round_start = true;
            if(lg_player1->getFirst() == true){
                    turn = 1;
            } else {
                turn = 2;
            }
        }
    }
    // If its not a test then this is used
    if(test == false){
        // Game is then created with current factories, players, mosaics and tilebag used as parameters
        NewGame* ng_lg = new NewGame(lg_player1, lg_player2, lg_factory1, lg_factory2, lg_factory3, lg_factory4,
            lg_factory5, lg_tilebag, lg_centralfactory, lg_roundCount, turn, lg_savegame, lg_boxlid);
        int rounds = lg_roundCount;
        // Partial round is called
        ng_lg->partialRound();
        rounds = rounds +1;
        // After that the normal game starts 
        while(rounds<=ROUNDS){
            std::cout << "=== ROUND " << rounds << " ===" << std::endl;
            ng_lg->round();
            // If round 5 then game is ended
            if (rounds == ROUNDS) {
                ng_lg->roundend();
                ng_lg->gameend();
            // else next round continues
            } else {
                ng_lg->roundend();
            }
            rounds = rounds + 1;
        }
    // If it is a test then the current factories, players and scores are printed
    } else {
        std::cout << std::endl << "=== TEST RESULTS ==="<< std::endl << std::endl;
        std::cout << "Player 1 Name: " << lg_player1->getName() << std::endl;
        std::cout << "Player 2 Name: " << lg_player2->getName() << std::endl << std::endl;
        std::cout << "Factories: " << std::endl;
        std::cout << "0: ";
        lg_centralfactory->printletters();
        std::cout << std::endl << "1: ";
        lg_factory1->printletters();
        std::cout << std::endl << "2: ";
        lg_factory2->printletters();
        std::cout << std::endl << "3: ";
        lg_factory3->printletters();
        std::cout << std::endl << "4: ";
        lg_factory4->printletters();
        std::cout << std::endl << "5: ";
        lg_factory5->printletters();
        std::cout << std::endl << std::endl << "Score for " << lg_player1->getName() << ": " << lg_player1->getPoints() << std::endl;
        lg_player1->getMosaic()->print();
        std::cout << std::endl << "Score for " << lg_player2->getName() << ": " << lg_player2->getPoints() << std::endl;
        lg_player2->getMosaic()->print();
        std::cout << std::endl;
        std::cout << "=== END TEST ==="<< std::endl << std::endl;
        }
}
// This method just prints out all the players info
void LoadGame::printplayer(Player *player)
{
    std::cout << std::endl
              << "TURN FOR PLAYER: " << player->getName() << std::endl;
    std::cout << "Factories: " << std::endl;
    std::cout << "0: ";
    lg_centralfactory->printletters();
    std::cout << std::endl
              << "1: ";
    lg_factory1->printletters();
    std::cout << std::endl
              << "2: ";
    lg_factory2->printletters();
    std::cout << std::endl
              << "3: ";
    lg_factory3->printletters();
    std::cout << std::endl
              << "4: ";
    lg_factory4->printletters();
    std::cout << std::endl
              << "5: ";
    lg_factory5->printletters();

    std::cout << std::endl
              << std::endl
              << "Mosaic for " << player->getName() << ": " << std::endl;
    player->getMosaic()->print();
}
// This method is used to make the players move
void LoadGame::move(Player *player, std::string move)
{
    // Splitting the move apart to get each individual part
    std::string fac = move.substr(FACT_INPUT, FACT_AND_TILE_ONE);
    std::string chosentile = move.substr(TILE_INPUT, FACT_AND_TILE_ONE);
    Colour chosenColour = lg_stringToEnum(chosentile);
    std::string row = move.substr(ROW_INPUT, ROW_LENGTH);

    //Creating a temporary factory to determine which factory was chosen based off user input
    BSTFactory *chosenfac = nullptr;
    bool central = false;
    // Selecting the factory
    if (fac == "1")
    {
        chosenfac = lg_factory1;
    }
    else if (fac == "2")
    {
        chosenfac = lg_factory2;
    }
    else if (fac == "3")
    {
        chosenfac = lg_factory3;
    }
    else if (fac == "4")
    {
        chosenfac = lg_factory4;
    }
    else if (fac == "5")
    {
        chosenfac = lg_factory5;
    }
    else if (fac == "0")
    {
        central = true;
    }
    Colour storageColour = Blank;
    int lastIndex = TILES_IN_FACTORY;
    // Unless row is 6 which means tiles go to broken
    if(row != "6"){
        for (int i = TILES_IN_FACTORY; i >= 0; --i)
        {   
            // Getting the last index of that storage row, if a tiles already there
            if (player->getMosaic()->getStorageTile(std::stoi(row) - 1, i)->getColour() != 
                Blank && player->getMosaic()->getStorageTile(std::stoi(row) - 1, i)->getColour() != No_Tile)
            {
                lastIndex = i;
            }
        }
        // The colour in that row is then set
        storageColour = player->getMosaic()->getStorageTile(std::stoi(row) -1, lastIndex)->getColour();
    }
    // If not the central factory
    if (central == false)
    {
        Tile *tileToBeMoved = nullptr;
        int count = 0;
        // This for loop goes through each tile in the factory

        // Getting the letter of the tile in index i of facotory
        // Checking if that matches the users selected tile

       if (chosenfac->contains(chosenColour))
        {
            // sets the temporary tile to the tile that will be moved
            // then increments a count of the number of tiles to be moved
            tileToBeMoved = new Tile(chosenColour);
            
            count = chosenfac->getCount(chosenColour);

            chosenfac->remove(chosenColour);
        }
        while (chosenfac->getBST()->getRoot() != nullptr) {
            TreeNode* node = chosenfac->getBST()->visitLeaf(chosenfac->getBST()->getRoot());

            lg_centralfactory->add(new Tile(*node->tile));

            chosenfac->remove(node->tile->getColour());
        }

        // moves tile from factory to storage (Row 6 goes to broken)
        if(row != "6"){
            // If there are more tiles then spots
            if (count > lastIndex){
                // Whatever can fit goes at the end
                player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), lastIndex, lastIndex - 1);
                // The rest go to broken
                for(int i = 0; i < count-lastIndex; i++){
                    player->getMosaic()->addBroken(tileToBeMoved, lg_boxlid);
                }
            // If all can fit then they go into the row
            } else {
                // If tiles are already there then they are added from that point onwards
                if (tileToBeMoved->getColour() == storageColour)
                {
                    player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), count, lastIndex - 1);
                }
                // If empty then they added at the start
                else
                {
                    player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), count);
                }
            }
        // Row 6 means broken, so all tiles are added to broken 
        } else {
            for(int i = 0; i<count; i++){
                player->getMosaic()->addBroken(tileToBeMoved, lg_boxlid);
            }
        }
        player->getMosaic()->checkForBroken(lg_boxlid);
    }
    // This is the same for the central factory
    // Difference is that extra tiles stay in factory
    else
    {
        if (lg_centralfactory->getTile(0)->getColour() == First_Player)
        {
            //the 0 at the end of this needs to be updated so it goes to the next free spot in the broken line
            player->getMosaic()->addBroken(lg_centralfactory->getTile(0), lg_boxlid);
            lg_centralfactory->remove(0);
        }
        Tile *tileToBeMoved = nullptr;
        int count = 0;
        // Have to set central factory size now because it will change throughout loop
        int size = lg_centralfactory->size();
        // This for loop goes through each tile in the factory
        for (int i = size - 1; i >= 0; i--)
        {
            // Getting the letter of the tile in index i of facotory
            // Checking if that matches the users selected tile
            if (lg_centralfactory->getTile(i)->getletter() == chosentile)
            {
                // sets the temporary tile to the tile that will be moved
                // then increments a count of the number of tiles to be moved
                tileToBeMoved = new Tile(*lg_centralfactory->getTile(i));
                ++count;

                lg_centralfactory->remove(i);
            }
        }
        // Same as before
        if(row != "6"){
            if (count > lastIndex){
                player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), lastIndex, lastIndex - 1);
                for(int i = 0; i < count-lastIndex; i++){
                    player->getMosaic()->addBroken(tileToBeMoved, lg_boxlid);
                }       
            } else{
                if (tileToBeMoved->getColour() == storageColour)
                {
                player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), count, lastIndex - 1);
                }
                else
                {
                    player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), count);
                }
            }
        } else {
            for(int i = 0; i<count; i++){
                player->getMosaic()->addBroken(tileToBeMoved, lg_boxlid);
            }
        }
        // moves tile from factory to storage
        player->getMosaic()->checkForBroken(lg_boxlid);
    }
}
// Returns true or false if round is over
bool LoadGame::roundover()
{
    // Sees if all factories are empty
    bool returnval = false;
    if (lg_factory1->isEmpty() == true && lg_factory2->isEmpty() == true && lg_factory3->isEmpty() == true &&
        lg_factory4->isEmpty() == true && lg_factory5->isEmpty() == true && lg_centralfactory->size() == 0)
    {
        returnval = true;
    }
    return returnval;
}

// Method for end of round
void LoadGame::roundend()
{   
    // Round is increased
    ++lg_roundCount;
    // Checks if the storage is full, this is used later in mosaic class
    lg_player1->getMosaic()->checkIfStorageIsFull();
    // End of round is called to automatically move mosaics, box lid is updated
    this->lg_boxlid = lg_player1->getMosaic()->endOfRound(lg_boxlid);
    // Scoring is done
    lg_player1->setPoints(lg_player1->getMosaic()->scoring(lg_player1->getPoints(), lg_roundCount));
    // Sets whose first
    lg_player1->setFirst(lg_player1->getMosaic()->checkfirst());
    // Box lid is updated wth broken
    this->lg_boxlid = lg_player1->getMosaic()->clearBroken(lg_boxlid);
    // Same as above
    lg_player2->getMosaic()->checkIfStorageIsFull();
    this->lg_boxlid = lg_player2->getMosaic()->endOfRound(lg_boxlid);
    lg_player2->setPoints(lg_player2->getMosaic()->scoring(lg_player2->getPoints(), lg_roundCount));
    lg_player2->setFirst(lg_player2->getMosaic()->checkfirst());
    this->lg_boxlid = lg_player2->getMosaic()->clearBroken(lg_boxlid);
    //If round does not equal 5 then scores are shown
    if(lg_roundCount != 5){
        std::cout << "Scores:" << std::endl;
        std::cout << "Player " << lg_player1->getName() << ": " << lg_player1->getPoints() << std::endl;
        std::cout << "Player " << lg_player2->getName() << ": " << lg_player2->getPoints() << std::endl;
        std::cout << "=== END OF ROUND ===" << std::endl;
        // Resetting factories
        factorySetUp();
    } else {
        std::cout << std::endl << "=== TEST RESULTS ==="<< std::endl << std::endl;
        std::cout << "Player 1 Name: " << lg_player1->getName() << std::endl;
        std::cout << "Player 2 Name: " << lg_player2->getName() << std::endl << std::endl;
        std::cout << "Factories: " << std::endl;
        std::cout << "0: ";
        lg_centralfactory->printletters();
        std::cout << std::endl << "1: ";
        lg_factory1->printletters();
        std::cout << std::endl << "2: ";
        lg_factory2->printletters();
        std::cout << std::endl << "3: ";
        lg_factory3->printletters();
        std::cout << std::endl << "4: ";
        lg_factory4->printletters();
        std::cout << std::endl << "5: ";
        lg_factory5->printletters();
        std::cout << std::endl << std::endl << "Score for " << lg_player1->getName() << ": " << lg_player1->getPoints() << std::endl;
        lg_player1->getMosaic()->print();
        std::cout << std::endl << "Score for " << lg_player2->getName() << ": " << lg_player2->getPoints() << std::endl;
        lg_player2->getMosaic()->print();
        std::cout << std::endl;
        std::cout << "=== END TEST ==="<< std::endl << std::endl;
    }
}

void LoadGame::factorySetUp(){
    // Resetting factories at the end of the round //
    
    // Adding F tile to central factory
    Tile *Ftile = new Tile(First_Player);
    lg_centralfactory->add(Ftile);
    // Filling factories getting first item from tile bag
    // If the tilebag is empty, refill with tiles from box lid
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (lg_tilebag->size() == 0) {
            lg_boxlid->refillTileBag(lg_tilebag);
        } 
        lg_factory1->add(lg_tilebag->get(0));
        lg_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (lg_tilebag->size() == 0) {
            lg_boxlid->refillTileBag(lg_tilebag);
        } 
        lg_factory2->add(lg_tilebag->get(0));
        lg_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (lg_tilebag->size() == 0) {
            lg_boxlid->refillTileBag(lg_tilebag);
        } 
        lg_factory3->add(lg_tilebag->get(0));
        lg_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (lg_tilebag->size() == 0) {
            lg_boxlid->refillTileBag(lg_tilebag);
        } 
        lg_factory4->add(lg_tilebag->get(0));
        lg_tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (lg_tilebag->size() == 0) {
            lg_boxlid->refillTileBag(lg_tilebag);
        } 
        lg_factory5->add(lg_tilebag->get(0));
        lg_tilebag->removeFront();
    }
}

Colour LoadGame::lg_stringToEnum(std::string col) {
    Colour colour = Red;
    if (col == "R") {
        colour = Red;
    } else if (col == "Y") {
        colour = Yellow;
    } else if (col == "B") {
        colour = Dark_Blue;
    } else if (col == "L") {
        colour = Light_Blue;
    } else if (col == "U") {
        colour = Black;
    } else if (col == "F") {
        colour = First_Player;
    }

    return colour;
}