#ifndef COSC_ASSIGN_NEW_G
#define COSC_ASSIGN_NEW_G

#include <iostream>
#include <fstream>
#include <sstream>

#include "CentralFactory.h"

#include "BSTFactory.h"

#include "LinkedList.h"
#include "Mosaic.h"
#include "Player.h"
#include "Tile.h"
#include "SaveGame.h"

#define START_INPUT 0
#define START_LENGTH 5
#define FACT_INPUT 5
#define TILE_INPUT 7
#define FACT_AND_TILE_LENGTH 2
#define FACT_AND_TILE_ONE 1
#define ROW_INPUT 9
#define ROW_LENGTH 1
#define ROUNDS 5
#define ROUND_START 0

class NewGame {
public:
    NewGame(std::string p1, std::string p2);

    NewGame(Player* p1, Player* p2, BSTFactory* bstFactory1, BSTFactory* bstFactory2, BSTFactory* bstFactory3,
     BSTFactory* bstFactory4, BSTFactory* bstFactory5, LinkedList* tilebag, CentralFactory* centralfactory, int round, int turn,
    SaveGame* savegame, BoxLid* boxlid);

    ~NewGame();

    /**
    * Used to start a new game
    */
    void start();

    /**
    * Enhancement function that starts the game with randomised tile bag using seed from user input
    */
    void start(int seed);

    /**
    * Used for each round
    */
    void round();

    /**
    * Used when loading in a game and the round is half done
    */
    void partialRound();

    /**
    * Used to get player 1 input
    */
    void p1Input();

    /**
    * Used to get player 2 input
    */
    void p2Input();

    /**
    * Used to save the game at the current state
    */
    void save(std::string file);

    /**
    * Used to print players factory and mosaci
    */
    void printplayer(Player* player);

    /**
    * Used to make a players move
    */
    void move(Player* player, std::string move);

    /**
    * Check for broken tiles in the mosaic
    */
    void checkForBroken(Player *player);

    /**
    * Used to check if the round is over
    */
    bool roundover();

    /**
    * End of round scoring and moving of tiles
    */
    void roundend();

    /**
    * Checks validity of players text
    */
    bool validText(std::string playermove);

    /**
    * Checks validity of playermove
    */
    bool validMove(Player* player, std::string playermove);

    /**
    * End of game method 
    */
    void gameend();

    /**
    * Used if eof is called
    */
    void exitgame();

    Colour ng_stringToEnum(std::string col);

    void refillTileBag();
    
private:

    Player* player1;
    Player* player2;
    CentralFactory* centralfactory;
    BSTFactory* bstFactory1;
    BSTFactory* bstFactory2;
    BSTFactory* bstFactory3;
    BSTFactory* bstFactory4;
    BSTFactory* bstFactory5;

    LinkedList* tilebag;
    SaveGame* savegame;

    BoxLid* boxlid;

    int roundCount;
    // Only used when loading in game
    int turn;
} ;

#endif //COSC_ASSIGN_NEW_G