#include "NewGame.h"

NewGame::NewGame(std::string p1, std::string p2)
{
    // Creating all objects
    this->player1 = new Player(p1, ROUND_START);
    this->player2 = new Player(p2, ROUND_START);
    this->bstFactory1 = new BSTFactory();
    this->bstFactory2 = new BSTFactory();
    this->bstFactory3 = new BSTFactory();
    this->bstFactory4 = new BSTFactory();
    this->bstFactory5 = new BSTFactory();
    this->centralfactory = new CentralFactory();
    this->tilebag = new LinkedList();
    this->savegame = new SaveGame();
    this->boxlid = new BoxLid();
    this->roundCount = ROUND_START;
    this->turn = ROUND_START;
}
// This is used to load in game
NewGame::NewGame(Player* p1, Player* p2, BSTFactory* bstFactory1, BSTFactory* bstFactory2, BSTFactory* bstFactory3,
     BSTFactory* bstFactory4, BSTFactory* bstFactory5, LinkedList* tilebag, CentralFactory* centralfactory, int round, int turn,
    SaveGame* savegame, BoxLid* boxlid){
            this->player1 = p1;
            this->player2 = p2;
            this->bstFactory1 = bstFactory1;
            this->bstFactory2 = bstFactory2;
            this->bstFactory3 = bstFactory3;
            this->bstFactory4 = bstFactory4;
            this->bstFactory5 = bstFactory5;
            this->centralfactory = centralfactory;
            this->tilebag = tilebag;
            this->savegame = savegame;
            this->boxlid = boxlid;
            this->roundCount = round;
            this->turn = turn;
}

NewGame::~NewGame()
{
    delete player1;
    delete player2;
    delete bstFactory1;
    delete bstFactory2;
    delete bstFactory3;
    delete bstFactory4;
    delete bstFactory5;
    delete centralfactory;
    delete tilebag;
    delete savegame;
}

void NewGame::start()
{
    // Setting up the tile bag
    // 10 tiles added 10 time = 100 tiles in tile bag which is the requirement
    for (int i = 0; i < 10; i++)
    {
        Tile *tile_red = new Tile(Red);
        tilebag->addBack(tile_red);
        Tile *tile_db = new Tile(Dark_Blue);
        tilebag->addBack(tile_db);
        Tile *tile_yellow = new Tile(Yellow);
        tilebag->addBack(tile_yellow);
        Tile *tile_lb = new Tile(Light_Blue);
        tilebag->addBack(tile_lb);
        Tile *tile_black = new Tile(Black);
        tilebag->addBack(tile_black);
    }
    // Saving the inital tile bag
    savegame->changeInital(tilebag->getTilesAsString());
    // Player 1 set first
    player1->setFirst(true);
}

void NewGame::start(int seed) {
    // Setting up the tile bag
    // 10 tiles added 10 time = 100 tiles in tile bag which is the requirement
    for (int i = 0; i < 10; i++)
    {
        Tile *tile_red = new Tile(Red);
        tilebag->addBack(tile_red);
        Tile *tile_db = new Tile(Dark_Blue);
        tilebag->addBack(tile_db);
        Tile *tile_yellow = new Tile(Yellow);
        tilebag->addBack(tile_yellow);
        Tile *tile_lb = new Tile(Light_Blue);
        tilebag->addBack(tile_lb);
        Tile *tile_black = new Tile(Black);
        tilebag->addBack(tile_black);
    }

    // shuffles the tile bag with the seed
    tilebag->shuffle(seed);

    // Saving the inital tile bag
    savegame->changeInital(tilebag->getTilesAsString());
    // Player 1 set first
    player1->setFirst(true);    
}

void NewGame::round()
{
    Tile *Ftile = new Tile(First_Player);
    // Adding F tile to central factory

    centralfactory->add(Ftile);
    // Filling factories getting first item from tile bag
    // before filling factories each iteration, checks to see if tile bag needs refilling
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (tilebag->size() == 0) {
            boxlid->refillTileBag(tilebag);
        } 
        bstFactory1->add(tilebag->get(0));
        tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (tilebag->size() == 0) {
            boxlid->refillTileBag(tilebag);
        } 
        bstFactory2->add(tilebag->get(0));
        tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (tilebag->size() == 0) {
            boxlid->refillTileBag(tilebag);
        } 
        bstFactory3->add(tilebag->get(0));
        tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (tilebag->size() == 0) {
            boxlid->refillTileBag(tilebag);
        } 
        bstFactory4->add(tilebag->get(0));
        tilebag->removeFront();
    }
    for (int i = 0; i < TILES_IN_FACTORY; i++)
    {
        if (tilebag->size() == 0) {
            boxlid->refillTileBag(tilebag);
        } 
        bstFactory5->add(tilebag->get(0));
        tilebag->removeFront();
    }
    // This is for if player two is first
    if(player2->getFirst() == true){
        p2Input();
    }
    // Rounds will keep going to round over
    while (roundover() == false)
    {
        p1Input();
        if (roundover() == false)
        {
            p2Input();
        }
    }
}
// Used for loaded in game when round is not finished
void NewGame::partialRound(){
    while(roundover() == false){
        if (turn == 1){
            p1Input();
            turn = 2;
        } else if (turn == 2){
            p2Input();
            turn = 1;
        }
    }
    roundend();
}

void NewGame::p1Input(){
    // Getting player input
    std::cout << std::endl;
    printplayer(player1);
    std::string playermove;
    std::cout << std::endl
                << "> ";
    std::getline(std::cin, playermove);
    // Checking the players move is valid
    while (playermove.substr(START_INPUT, START_LENGTH) == "Save " || playermove.substr(START_INPUT, START_LENGTH) == "save " ||
            !validText(playermove) || !validMove(player1, playermove) ||
            player1->getMosaic()->alreadyThere(stoi(playermove.substr(ROW_INPUT, ROW_LENGTH)), playermove.substr(TILE_INPUT, ROW_LENGTH)) 
            ||player1->getMosaic()->returnIfStorageIsFull(stoi(playermove.substr(ROW_INPUT, ROW_LENGTH)))){   
        // If control D given then game is closed
        if(std::cin.eof()){
            exitgame();
        }
        // If player saves game
        if(playermove.substr(START_INPUT, START_LENGTH) == "Save " || playermove.substr(START_INPUT, START_LENGTH) == "save "){
            std::stringstream ss{playermove};
            std::string file;
            ss >> file;
            ss >> file;
            // Save is called
            save(file);
            std::cout << "Game succesfully saved to '" << file << "'" << std::endl;
            std::cout << std::endl
                    << "> ";
            std::getline(std::cin, playermove);
        } else {
            std::cout << "Invalid Input (Format is: Turn <factory> <tile> <row>)";
            std::cout << std::endl
                    << "> ";
            std::getline(std::cin, playermove);
        }       
    }
    std::cout << std::endl;
    // If players move is valid then game is started
    if (playermove.substr(START_INPUT, START_LENGTH) == "Turn " || playermove.substr(START_INPUT, START_LENGTH) == "turn ")
    {
        // Player makes move
        move(player1, playermove);
        // Moved is saved
        savegame->add(playermove);
    }
}
// Same as P1 except for P2
void NewGame::p2Input(){
    printplayer(player2);
    std::string playermove2;
    std::cout << std::endl
            << "> ";
    std::getline(std::cin, playermove2);
    while (playermove2.substr(START_INPUT, START_LENGTH) == "Save " || playermove2.substr(START_INPUT, START_LENGTH) == "save " ||
        !validText(playermove2) || !validMove(player2, playermove2)||
        player2->getMosaic()->alreadyThere(stoi(playermove2.substr(ROW_INPUT, ROW_LENGTH)), playermove2.substr(TILE_INPUT, ROW_LENGTH)) 
        || player2->getMosaic()->returnIfStorageIsFull(stoi(playermove2.substr(ROW_INPUT, ROW_LENGTH))))
    {
        if(std::cin.eof()){
            exitgame();
        }
        if(playermove2.substr(START_INPUT, START_LENGTH) == "Save " || playermove2.substr(START_INPUT, START_LENGTH) == "save "){
            std::stringstream ss{playermove2};
            std::string file;
            ss >> file;
            ss >> file;
            save(file);
            std::cout << "Game succesfully saved to '" << file << "'" << std::endl;
            std::cout << std::endl
                    << "> ";
            std::getline(std::cin, playermove2);
        } else{
            std::cout << "Invalid Input (Format is: Turn <factory> <tile> <row>";
            std::cout << std::endl
                    << "> ";
            std::getline(std::cin, playermove2);
        }
    }
    std::cout << std::endl;
    if (playermove2.substr(START_INPUT, START_LENGTH) == "Turn " || playermove2.substr(START_INPUT, START_LENGTH) == "turn ")
    {
        move(player2, playermove2);
        savegame->add(playermove2);
    }
}

// When save game is called
void NewGame::save(std::string file)
{
    std::ofstream savefile;
    savefile.open(file);
    // Inital tilebag saved
    savefile << savegame->returnInital();
    savefile << "\n";
    // Names saved
    savefile << player1->getName() << "\n";
    savefile << player2->getName() << "\n";
    // Goes through all moves and saves them
    for (int i = 0; i < savegame->size(); ++i)
    {
        savefile << savegame->getMove(i) << "\n";
    }
    savefile.close();
}
// Prints player info
void NewGame::printplayer(Player *player)
{
    std::cout << std::endl
              << "TURN FOR PLAYER: " << player->getName() << std::endl;
    std::cout << "Factories: " << std::endl;
    std::cout << "0: ";
    centralfactory->printletters();
    std::cout << std::endl;
    std::cout << "1: ";
    bstFactory1->printletters();
    std::cout << "2: ";
    bstFactory2->printletters();
    std::cout << "3: ";
    bstFactory3->printletters();
    std::cout << "4: ";
    bstFactory4->printletters();
    std::cout << "5: ";
    bstFactory5->printletters();

    std::cout << std::endl
              << std::endl
              << "Mosaic for " << player->getName() << ": " << std::endl;
    player->getMosaic()->print();
}

void NewGame::move(Player *player, std::string move)
{
    // Splitting the move apart to get each individual part
    std::string fac = move.substr(FACT_INPUT, 1);
    std::string chosentile = move.substr(TILE_INPUT, 1);
    Colour chosenColour = ng_stringToEnum(chosentile);
    std::string row = move.substr(ROW_INPUT, ROW_LENGTH);

    //Creating a temporary factory to determine which factory was chosen based off user input
    BSTFactory* chosenfac = nullptr;
    bool central = false;
    // Selecting the factory
    if (fac == "1")
    {
        chosenfac = bstFactory1;
    }
    else if (fac == "2")
    {
        chosenfac = bstFactory2;
    }
    else if (fac == "3")
    {
        chosenfac = bstFactory3;
    }
    else if (fac == "4")
    {
        chosenfac = bstFactory4;
    }
    else if (fac == "5")
    {
        chosenfac = bstFactory5;
    }
    else if (fac == "0")
    {
        central = true;
    }
    Colour storageColour = Blank;
    int lastIndex = TILES_IN_FACTORY;
     // Unless row is 6 which means tiles go to broken
    if(row != "6"){
        for (int i = 4; i >= 0; --i)
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

        // Getting the letter of the tile in index i of facotory
        // Checking if that matches the users selected tile
        if (chosenfac->contains(chosenColour))
        {
            // sets the temporary tile to the tile that will be moved
            // then sets tile count to the node's count in the factory bst
            // then removes a single node from the bst
            tileToBeMoved = new Tile(chosenColour);
            count = chosenfac->getCount(chosenColour);
            chosenfac->remove(chosenColour);
        }

        // while the factory bst's root node is not nullptr
        while (chosenfac->getBST()->getRoot() != nullptr) {
            // instantiate a new node as a leaf node of the factory bst
            TreeNode* node = chosenfac->getBST()->visitLeaf(chosenfac->getBST()->getRoot());
            // add a copy of it to the central factory
            centralfactory->add(new Tile(*node->tile));
            // remove the node from the factory bst 
            chosenfac->remove(node->tile->getColour());
        }

        // moves tile from factory to storage
        if(row != "6"){
            // If there are more tiles then spots
            if (count > lastIndex){
                // Whatever can fit goes at the end
                player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), lastIndex, lastIndex - 1);
                 // The rest go to broken
                for(int i = 0; i < count-lastIndex; i++){
                    player->getMosaic()->addBroken(tileToBeMoved, boxlid);
                }
            // If all can fit then they go into the row
            } else {
                // If tiles are already there then they are added from that point onwards
                if (tileToBeMoved->getColour() == storageColour)
                {
                    if(player->getMosaic()->Brokensize() == BROKEN_SIZE){
                        tilebag->addBack(tileToBeMoved);
                    } else{
                        player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), count, lastIndex - 1);
                    }
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
                player->getMosaic()->addBroken(tileToBeMoved, boxlid);
            }
        }
            
        player->getMosaic()->checkForBroken(boxlid);
        // Printing the mosaic just to check how its gone
        player->getMosaic()->print();
        std::cout << std::endl;
    }
    // This is the same for the central factory
    // Difference is that extra tiles stay in factory
    else
    {
        if (centralfactory->getTile(0)->getColour() == First_Player)
        {
            //the 0 at the end of this needs to be updated so it goes to the next free spot in the broken line
            player->getMosaic()->addBroken(centralfactory->getTile(0), boxlid);
            centralfactory->remove(0);
        }
        Tile *tileToBeMoved = nullptr;
        int count = 0;
        // Have to set central factory size now because it will change throughout loop
        int size = centralfactory->size();
        // This for loop goes through each tile in the factory
        for (int i = size - 1; i >= 0; i--)
        {
            // Getting the letter of the tile in index i of facotory
            //std::string tilecol =
            // Checking if that matches the users selected tile
            if (centralfactory->getTile(i)->getletter() == chosentile)
            {
                // sets the temporary tile to the tile that will be moved
                // then increments a count of the number of tiles to be moved
                tileToBeMoved = new Tile(*centralfactory->getTile(i));
                ++count;

                centralfactory->remove(i);
            }
        }
        if(row != "6"){
            if (count > lastIndex){
                player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), lastIndex, lastIndex - 1);
                for(int i = 0; i < count-lastIndex; i++){
                    if(player->getMosaic()->Brokensize() == BROKEN_SIZE){
                        tilebag->addBack(tileToBeMoved);
                    }else{
                        player->getMosaic()->addBroken(tileToBeMoved, boxlid);
                    }
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
                player->getMosaic()->addBroken(tileToBeMoved, boxlid);
            }
        }
        // moves tile from factory to storage
        // tileToBeMoved->printLetter();
        //player->getMosaic()->setStorageRow(tileToBeMoved, std::stoi(row), count);
        player->getMosaic()->checkForBroken(boxlid);
        // Printing the mosaic just to check how its gone
        player->getMosaic()->print();
        std::cout << std::endl;
    }
}
// Returns true or false if round is over
bool NewGame::roundover()
{
    // Sees if all factories are empty
    bool returnval = false;
    if (bstFactory1->isEmpty() == true && bstFactory2->isEmpty() == true && bstFactory3->isEmpty() == true &&
        bstFactory4->isEmpty() == true && bstFactory5->isEmpty() == true && centralfactory->size() == 0)
    {
        returnval = true;
    }
    return returnval;
}
// Method for end of round
void NewGame::roundend()
{
    // Round is increased
    ++roundCount;
    // Checks if the storage is full, this is used later in mosaic class
    player1->getMosaic()->checkIfStorageIsFull();
    // End of round is called to automatically move mosaics, box lid is updated
    this->boxlid = player1->getMosaic()->endOfRound(boxlid);
    // Scoring is done
    player1->setPoints(player1->getMosaic()->scoring(player1->getPoints(), roundCount));
    // Sets whose first
    player1->setFirst(player1->getMosaic()->checkfirst());
    // Box lid is updated wth broken
    this->boxlid = player1->getMosaic()->clearBroken(boxlid);
    // Same as above
    player2->getMosaic()->checkIfStorageIsFull();
    this->boxlid = player2->getMosaic()->endOfRound(boxlid);
    player2->setPoints(player2->getMosaic()->scoring(player2->getPoints(), roundCount));
    player2->setFirst(player2->getMosaic()->checkfirst());
    this->boxlid = player2->getMosaic()->clearBroken(boxlid);
    if(roundCount != ROUNDS){
        std::cout << "=== END OF ROUND ===" << std::endl << std::endl;
    }
}
// This validates users input
bool NewGame::validText(std::string playermove)
{
    // First part must be turn
    bool returnval = false;
    if ((playermove.substr(START_INPUT, START_LENGTH) == "turn " || playermove.substr(START_INPUT, START_LENGTH) == "Turn ") && 
            playermove.size() != 10)
    {
        returnval = false;
    }
    else if (playermove.substr(START_INPUT, START_LENGTH) == "turn " || playermove.substr(START_INPUT, START_LENGTH) == "Turn ")
    {
        // Next must be a valid factory
        if (playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "0 " || playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "1 "
                || playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "2 " || 
                playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "3 " || 
                playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "4 " || 
                playermove.substr(FACT_INPUT, FACT_AND_TILE_LENGTH) == "5 ")
        {
            // Tile must be valid
            if (playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "R " || 
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "Y " ||
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "B " || 
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "L " || 
                    playermove.substr(TILE_INPUT, FACT_AND_TILE_LENGTH) == "U ")
            {
                // Row must be valid
                if (playermove.substr(ROW_INPUT, ROW_LENGTH) == "1" || playermove.substr(ROW_INPUT, ROW_LENGTH) == "2" || 
                        playermove.substr(ROW_INPUT, ROW_LENGTH) == "3" || playermove.substr(ROW_INPUT, ROW_LENGTH) == "4" || 
                        playermove.substr(ROW_INPUT, ROW_LENGTH) == "5" || playermove.substr(ROW_INPUT, ROW_LENGTH) == "6")
                {
                    returnval = true;
                }
                else
                {
                    returnval = false;
                }
            }
            else
            {
                returnval = false;
            }
        }
        else
        {
            returnval = false;
        }
    }
    // If save then its valid
    else if (playermove.substr(START_INPUT, START_LENGTH) == "save " || playermove.substr(START_INPUT, START_LENGTH) == "Save ")
    {
        returnval = true;
    }
    else
    {
        returnval = false;
    }

    return returnval;
}
// Checks if the move is valid
bool NewGame::validMove(Player *player, std::string playermove)
{
    // Input is broken apart
    std::string fac = playermove.substr(FACT_INPUT, FACT_AND_TILE_ONE);
    std::string chosentile = playermove.substr(TILE_INPUT, FACT_AND_TILE_ONE);
    Colour chosenColour = ng_stringToEnum(chosentile);
    std::string row = playermove.substr(ROW_INPUT, ROW_LENGTH);
    bool check1 = false;
    bool check2 = false;
    bool check3 = false;
    bool returnval = false;
    // Tile must be same as row colour or row must be empty
    if (player->getMosaic()->checkrowcolour(std::stoi(row)) == chosentile ||
        player->getMosaic()->checkrowcolour(std::stoi(row)) == "." || row == "6")
    {
        check1 = true;
    }
    // Goes though to make sure tile is in factory
    if (fac == "1")
    {
        if (!bstFactory1->isEmpty())
        {
            check2 = true;
        }

        if (bstFactory1->contains(chosenColour))
        {
            check3 = true;
        }

    }
    else if (fac == "2")
    {
        if (!bstFactory2->isEmpty())
        {
            check2 = true;
        }

        if (bstFactory2->contains(chosenColour))
        {
            check3 = true;
        }
    }
    else if (fac == "3")
    {
        if (!bstFactory3->isEmpty())
        {
            check2 = true;
        }

        if (bstFactory3->contains(chosenColour))
        {
            check3 = true;
        }
    }
    else if (fac == "4")
    {
        if (!bstFactory4->isEmpty())
        {
            check2 = true;
        }

        if (bstFactory4->contains(chosenColour))
        {
            check3 = true;
        }
    }
    else if (fac == "5")
    {
        if (!bstFactory5->isEmpty())
        {
            check2 = true;
        }

        if (bstFactory5->contains(chosenColour))
        {
            check3 = true;
        }
    }
    else if (fac == "0")
    {
        if (centralfactory->size() > 0)
        {
            check2 = true;
        }
        for (int i = 0; i < centralfactory->size(); i++)
        {
            if (centralfactory->getTile(i)->getletter() == chosentile)
            {
                check3 = true;
            }
        }
    }
    // If all is true then move is valid
    if (check1 == true && check2 == true && check3 == true)
    {
        returnval = true;
    }

    return returnval;
}
// Ends the game and prints final score and winner
void NewGame::gameend() {
    std::cout << "=== GAME OVER ===" << std::endl;
    std::cout << "Final Scores:" << std::endl;
    std::cout << "Player " << player1->getName() << ": " << player1->getPoints() << std::endl;
    std::cout << "Player " << player2->getName() << ": " << player2->getPoints() << std::endl;

    if (player1->getPoints() > player2->getPoints()) {
        std::cout << "Player " << player1->getName() << " wins!" << std::endl;
    } else {
            std::cout << "Player " << player2->getName() << " wins!" << std::endl;
    }
}
// Used when eof is given
void NewGame::exitgame(){
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}

Colour NewGame::ng_stringToEnum(std::string col) {
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

void NewGame::refillTileBag() {
    boxlid->refillTileBag(tilebag);
}