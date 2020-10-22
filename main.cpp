#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

#include "NewGame.h"
#include "LoadGame.h"

#define MAX_ROUNDS 5

//Methods
void credits(); 
void newgame();

void newgame(int seed);

void loadgame();
void validfile();
void printmenu();

void printmenu(int seed);

void endgame();
void test(std::string fname);

// int containing seed from user input
int seed;

// Used to print out the main menu
void printmenu(){
    std::string option;
    bool stop = false;
    std::cout << std::endl << "Welcome to Azul" << std::endl << "---------------" << std::endl;
    //This will loop until input is valid
    while(stop == false){
        std::cout << std::endl << "Menu" << std::endl << "----" << std::endl;
        std::cout << "1. New game" << std::endl << "2. Load game" << std::endl << "3. Credits" << std::endl <<"4. Quit";
        std::cout << std::endl << std::endl << "> ";
        std::getline(std::cin, option);
        if(!std::cin.eof()){
            while(option != "1" && option != "2" && option != "3" && option != "4" && !std::cin.eof()){
                std::cout << "Invalid Input";
                std::cout << std::endl << "> ";
                std::getline(std::cin, option);
            }
            // Option one starts a new game
            if(option == "1"){
                newgame();
                stop = true;
            // Option two loads in a game
            } else if(option == "2"){
                loadgame();
            // Option 3 shows the credits
            } else if(option == "3"){
                credits();
            // Option 3 four exits the game
            } else if(option == "4"){
                stop = true;
            } else {
            stop = true;
            }
        } else {
            endgame();
        }
    } 
}

// Used to print out the main menu
void printmenu(int seed){
    std::string option;
    bool stop = false;
    std::cout << std::endl << "Welcome to Azul" << std::endl << "---------------" << std::endl;
    //This will loop until input is valid
    while(stop == false){
        std::cout << std::endl << "Menu" << std::endl << "----" << std::endl;
        std::cout << "1. New game" << std::endl << "2. Load game" << std::endl << "3. Credits" << std::endl <<"4. Quit";
        std::cout << std::endl << std::endl << "> ";
        std::getline(std::cin, option);
        if(!std::cin.eof()){
            while(option != "1" && option != "2" && option != "3" && option != "4" && !std::cin.eof()){
                std::cout << "Invalid Input";
                std::cout << std::endl << "> ";
                std::getline(std::cin, option);
            }
            // Option one starts a new game
            if(option == "1"){
                newgame(seed);
                stop = true;
            // Option two loads in a game
            } else if(option == "2"){
                loadgame();
            // Option 3 shows the credits
            } else if(option == "3"){
                credits();
            // Option 3 four exits the game
            } else if(option == "4"){
                stop = true;
            } else {
            stop = true;
            }
        } else {
            endgame();
        }
    } 
}

// When called this will start a new game
void newgame(){
    std::cout << "=== Starting New Game ===" << std::endl;
    // Setting up players
    std::string name1;
    std::string name2;
    std::cout << std::endl << "Enter a name for player 1" << std::endl << "> ";
    std::getline(std::cin, name1);
    if(std::cin.eof()){
        endgame();
    }
    std::cout << std::endl << "Enter a name for player 2" << std::endl << "> ";
    std::getline(std::cin, name2);
    if(std::cin.eof()){
        endgame();
    }
    std::cout << std::endl << "Let's Play!" << std::endl;
    // New game class is called with players name used as parameters
    NewGame* ng = new NewGame(name1, name2);
    // Start method called which sets up game
    ng->start();
    int rounds = 1;
    // Rounds will be looped through untill 5 have been done, then game will finish
    while(rounds<=MAX_ROUNDS){
        std::cout << "=== ROUND " << rounds << " ===" << std::endl;
        // Round method goes though one round
        ng->round();
        if (rounds == MAX_ROUNDS) {
            // Roundend ends the round totaling score
            ng->roundend();
            // Game end gets final score and decides winner
            ng->gameend();
        } else {
            ng->roundend();
        }
        rounds = rounds + 1;
    }
    // Deleting the new game from memory
    delete ng;
}

void newgame(int seed) {
    std::cout << "=== Starting New Game ===" << std::endl;
    // Setting up players
    std::string name1;
    std::string name2;
    std::cout << std::endl << "Enter a name for player 1" << std::endl << "> ";
    std::getline(std::cin, name1);
    if(std::cin.eof()){
        endgame();
    }
    std::cout << std::endl << "Enter a name for player 2" << std::endl << "> ";
    std::getline(std::cin, name2);
    if(std::cin.eof()){
        endgame();
    }
    std::cout << std::endl << "Let's Play!" << std::endl;
    // New game class is called with players name used as parameters
    NewGame* ng = new NewGame(name1, name2);
    // Start method called which sets up game
    ng->start(seed);
    int rounds = 1;
    // Rounds will be looped through untill 5 have been done, then game will finish
    while(rounds<=MAX_ROUNDS){
        std::cout << "=== ROUND " << rounds << " ===" << std::endl;
        // Round method goes though one round
        ng->round();
        if (rounds == MAX_ROUNDS) {
            // Roundend ends the round totaling score
            ng->roundend();
            // Game end gets final score and decides winner
            ng->gameend();
        } else {
            ng->roundend();
        }
        rounds = rounds + 1;
    }
    // Deleting the new game from memory
    delete ng;
}

// This is used to determine wether a file has the correct format so that it can be used
bool validFile(std::string filename){
    bool returnval = true;
    // Opening file and storing each line as an element of a vector
    std::vector<std::string> lines_array;
    std::string line;
    std::ifstream loadfile;
    loadfile.open(filename);
    while(!loadfile.eof()){
	    std::getline(loadfile,line);
        lines_array.push_back(line);
    }
	loadfile.close();
    if(lines_array[0].length() < 100){
        returnval = false;
    }
    //Checking tilebag only has legal tiles
    for(int i = 0; (unsigned) i<lines_array[0].length(); i++){
        if(lines_array[0].substr(i,1) != "R" && lines_array[0].substr(i,1) != "L" && lines_array[0].substr(i,1) !="U" && 
            lines_array[0].substr(i,1) != "B" && lines_array[0].substr(i,1) != "Y"){
                returnval = false;
        }
    }
    //Checking first word of every move is turn
    for(int i = 3; (unsigned) i<lines_array.size(); i++){
        if(lines_array[i].substr(START_INPUT,4) != "turn" && lines_array[i].substr(START_INPUT,4) != "Turn" && 
            lines_array[i].substr(START_INPUT,4) != ""){
                returnval = false;
        }
    }
    //Checking factory choice is legal
    for(int i = 3; (unsigned) i<lines_array.size(); i++){
        if(lines_array[i].substr(START_INPUT,4) != ""){
            if(lines_array[i].substr(FACT_INPUT, 2) != "0 " &&  lines_array[i].substr(FACT_INPUT, 2) != "1 " && 
                lines_array[i].substr(FACT_INPUT, 2) != "2 " && lines_array[i].substr(FACT_INPUT, 2) != "3 " &&
                lines_array[i].substr(FACT_INPUT, 2) != "4 " && lines_array[i].substr(FACT_INPUT, 2) != "5 "){
                    returnval = false;
            }
        }
    }
    //Checking if tile chosen is legal
    for(int i = 3; (unsigned) i<lines_array.size(); i++){
        if(lines_array[i].substr(START_INPUT,4) != ""){
            if(lines_array[i].substr(TILE_INPUT, 2) != "R " && lines_array[i].substr(TILE_INPUT, 2) != "Y " && 
                lines_array[i].substr(TILE_INPUT, 2) != "B " && lines_array[i].substr(TILE_INPUT, 2) != "L " && 
                lines_array[i].substr(TILE_INPUT, 2) != "U "){
                    returnval = false;
            }
        }
    }
    //Checking that row selection is legal
    for(int i = 3; (unsigned) i<lines_array.size(); i++){
        if(lines_array[i].substr(START_INPUT,4) != ""){
            if(lines_array[i].substr(ROW_INPUT, 1) != "1" && lines_array[i].substr(ROW_INPUT, 1) != "2" && 
                lines_array[i].substr(ROW_INPUT, 1) != "3" && lines_array[i].substr(ROW_INPUT, 1) != "4" && 
                lines_array[i].substr(ROW_INPUT, 1) != "5" && lines_array[i].substr(ROW_INPUT, 1) != "6"){
                    returnval = false;
            }
        }
    }
    return returnval;
}
/** Contract
 * Input: Save file must contain legal turns (e.g can't put tile in row with a different colour tile or can't go in a row
 * when the same tile is already in the same row on the mosaic). Save file must also not be a finished game.
 * Output: Game will load up
 * Load Game will validate that the file has the correct format (e.g tilebag, players then turns)
 * It will also ensure factory choices are from 0-5, tile colours are correct and row number is correct
 * However if the save file has illegal turns (such as taking R from factory 1 when that factory doesn't have a R tile) 
 * then the game will crash
 */
void loadgame(){
    // Getting save file
    std::string filename;
    std::cout << "Enter the filename from which load a game" << std::endl << "> ";
    std::getline(std::cin, filename);
    if(std::cin.eof()){
        endgame();
    }
    std::ifstream loadfile;
    loadfile.open(filename);
    // Checking if the file exists and is valid
    try{

        if(!loadfile.fail() && validFile(filename)){
            // If correct load game wil be created
            LoadGame* loadg = new LoadGame();
            // File is read in, game is set up and game beings loading in
            loadg->readfile(filename);
            loadg->setup();
            // Load game class will continue the game
            loadg->round(false);
            delete loadg;
        } else {
            std::cout << "No valid file found. Going back to menu." << std::endl;
        }
    // If its not valid game will catch exception
    } catch(std::exception& e){
        std::cout << "No valid file found. Going back to menu." << std::endl;
    }
    loadfile.close();
}
// Prints credits
void credits(){
    std::cout << std::endl << "CREDITS" << std::endl << "---------" << std::endl;
    // Marc info
    std::cout << std::endl << "---------------" << std::endl << "Name: Marc Mento" << std::endl 
        << "Student ID: s3839668" << std::endl;
    std::cout << "Email: s3839668@student.rmit.edu.au" << std::endl << "---------------" << std::endl;
    // Jack info
    std::cout << std::endl << "---------------" << std::endl << "Name: Jack Allen" << std::endl 
        << "Student ID: s3832293" << std::endl;
    std::cout << "Email: s3832293@student.rmit.edu.au" << std::endl << "---------------" << std::endl;
    // Jia info
    std::cout << std::endl << "---------------" << std::endl << "Name: Jia Bang Vuong" << std::endl 
        << "Student ID: s3785886" << std::endl;
    std::cout << "Email: s3785886@student.rmit.edu.au" << std::endl  << "---------------" << std::endl;
}
// Test method called when command line argument -t is used
/** Contract
 * Input: Save file must contain legal turns (e.g can't put tile in row with a different colour tile or can't go in a row
 * when the same tile is already in the same row on the mosaic)
 * Output: Test will load up and print
 * Same contract as before
 */
void test(std::string fname){
    // Loading in file
    std::ifstream loadfile;
    loadfile.open(fname);
    // This will try to load in the file and validate it
    try{
        if(validFile(fname)){
            LoadGame* testg = new LoadGame();
            testg->readfile(fname);
            testg->setup();
            testg->round(true);
            delete testg;
        } else {
            std::cout << "No valid file found. Closing game." << std::endl;
        }
    // If it isn't valid the expection will be caught and the file closed
    } catch(std::exception& e){
        std::cout << "No valid file found. Closing game." << std::endl;
    }
    loadfile.close();
}

void endgame(){
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}

// Main with command line argument checks
int main(int argc, char** argv){
    // If 3 command line arguments are found then they will be check
    if(argc >= 3){
        std::string strArgv(argv[1]);
        std::string strArgv2(argv[2]);
        std::ifstream loadfile;
        loadfile.open(strArgv2);
        // If file can be opened and 2nd argument is -t then test will begin
        if(strArgv == "-t" && !loadfile.fail()){
            loadfile.close();
            test(strArgv2);
        } else if (strArgv == "-s") {
            try {
                seed = std::stoi(strArgv2);
                printmenu(seed);
            } catch (std::invalid_argument& bc) {
                std::cerr << "Error: Third argument is not a number" << std::endl;
            }
        } else {
            std::cout << "Error: Incorrect command line argument or Incorrect file name" << std::endl;
        }
    } else if(argc == 2){
        std::cout << "Error: Incomplete number of command line argument" << std::endl;
    // If not in test mode then normal game starts
    } else {
        printmenu();
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}