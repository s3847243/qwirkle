
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include "GameEngine.h"
#include "Util.h"

GameEngine::~GameEngine() {
    // No deleting as nothing is allocated on the heap.
    // Can change if we're only allowed to new instances.
}

GameEngine::GameEngine(std::string player1Name, std::string player2Name,std::string player3Name) {
    display = Display();
    tileBag = LinkedList();
    temptileBag = LinkedList();
    board = Board();
    player1 = Player(player1Name);
    player2 = Player(player2Name);
    player3 = Player(player3Name);
    currentPlayer = &player1;
    done = true;

    
    createTileBag();
    shuffleTiles(nullptr);
    
    for(int i = 0; i < HAND_SIZE; ++i) {
        player1.getHand().push_back(tileBag.pop_front());
    }

    for(int i = 0; i < HAND_SIZE; ++i) {
        player2.getHand().push_back(tileBag.pop_front());
    }
    for(int i = 0; i < HAND_SIZE; ++i) {
        player3.getHand().push_back(tileBag.pop_front());
    }
}


GameEngine::GameEngine() {
    display = Display();
    tileBag = LinkedList();
    board = Board();
    currentPlayer = &player1;
}


bool GameEngine::gameIsOver() {
    return (player1.getHand().size() == 0 || player2.getHand().size() == 0 || player3.getHand().size() == 0) &&
                                                       tileBag.size() == 0;
}

void GameEngine::checkError() {
    if(errorMessage != NO_ERROR) {
        display.print(errorMessage);
        errorMessage = NO_ERROR;
    }
}

void GameEngine::start() {
    std::string input = "";
    bool quit = false;

    while(!quit) {

        display.print(*currentPlayer,player1,player2,player3);
        display.print(board);
        display.printHand(*currentPlayer);
        bool invalidInput = true;

        while(invalidInput) {
            display.prompt();

            if(getline(std::cin, input).eof()) {
                invalidInput = false;
                quit = true;
            }

            else if(parseInput(input)) {
                if(executeCommand(&quit)){
                    invalidInput = false;
                }else if(getDone() == true){   // just so that it continues
                    invalidInput = false;

                }
                
            } else errorMessage = "Please enter a valid command!";

            checkError();
        }
        //currentPlayer = *currentPlayer == player1 ? &player2 : &player1;
        if (getDone() == false)
        {
            if(*currentPlayer == player1){
                currentPlayer = &player2;
            }else if(*currentPlayer == player2){
                currentPlayer = &player3;
            }else if (*currentPlayer == player3){
                currentPlayer = &player1;
            }
        }
        
        
        // placing multiple tiles, make valid = false, then when its done for them they should press type DONE...this will either skip or basically place the tiles.
        // have a double if condition which checks that...if currentPlayer is PLayer 1 make it player 2 ....else if its player 2 then make player 3....else if if player 3 then make it player 1
        if(gameIsOver()){
            quit = true;
        }
        if(quit == true){
            display.gameOverMessage(player1,player2,player3);

        }
    }
}


bool GameEngine::executeCommand(bool* quit) {
    bool valid = false;
    int y = tokens.boardLoc[0] - 'A';
    int x = -1;

    // Handle double digit column
    if(tokens.boardLoc.length() == 3)   x += doubleDigitCol(tokens.boardLoc);
    else                                x += charToInt(tokens.boardLoc[1]);

    if(PLACE == tokens.command) {
        Tile* tile = currentPlayer->getTile(tokens.tileCode);

        if(nullptr != tile) {
            if(board.legalPlacementAt(x, y, tile)) {
                board.addToBoard(new Tile(*tile), x, y);

                currentPlayer->updateScore(board.calcScoreFrom(x, y));

                Tile* replacement = tileBag.pop_front();

                currentPlayer->replaceTile(tile, replacement);
                done = true;

            } else errorMessage = "Tile needs to be placed in a valid location";
        } else errorMessage = "valid Tile needs to be placed";
    }else if(DONE == tokens.command){
        valid = true;
        done = false;

    }else if(SKIP == tokens.command){
        valid = true;
        done = false;
    }
    else if(REPLACE == tokens.command) {
        Tile* playerTile = currentPlayer->getTile(tokens.tileCode);
        Tile* replacement = tileBag.pop_front();

        if(nullptr != playerTile) {
            Tile* copyPlayerTile = new Tile(*currentPlayer->getTile(tokens.tileCode));

            if(nullptr != replacement) {
                currentPlayer->replaceTile(playerTile, replacement);
                tileBag.push_back(copyPlayerTile);

                display.print(currentPlayer->getHand());
                done = false;
                valid = true;
            } else errorMessage = "There are no more tiles in the bag!";
        } else errorMessage = "You do not have that tile!";
    }

    else if(tokens.command == SAVE) {
        save();
        valid = true;
    }
    // Don't care if it fails, only care if it passes
    try {
        if(QUIT == stoi(tokens.command)) {
            valid = true;
            *quit = true;
        }
    } catch(...) {}
    return valid;
}


bool GameEngine::parseInput(std::string input) {
    std::stringstream inputStream(input);
    std::string tokens[MAX_ARGS] = {};
    bool valid = false;

    for(int i = 0; i < MAX_ARGS && inputStream >> tokens[i]; ++i);
    //    toLowerCase(tokens[i]);

    if(PLACE == tokens[0]) {
        this->tokens.command = PLACE;

        if(validTile(tokens[1])) {

            if(tokens[2] == AT && validLoc(tokens[3])) {
                this->tokens.boardLoc = tokens[3];
                valid = true;
                done = true;
            }
        }
    }else if (DONE == tokens[0]){
        this->tokens.command = DONE;
        done = false;
        valid = true;
    }else if (SKIP == tokens[0]){
        this->tokens.command = SKIP;
        done = false;
        valid = true;
    }
    
    else if(REPLACE == tokens[0]) {
        this->tokens.command = REPLACE;
        
        if(validTile(tokens[1])) {
            this->tokens.tileCode = tokens[1];
            valid = true;
        }
    }
    else if(SAVE == tokens[0]) {
        this->tokens.command = SAVE;
        this->tokens.saveFile = tokens[1];
        valid = true;
    }else if(HELP == tokens[0]){
        this->tokens.command = HELP;
        display.printHelp();
        
    }
    
    // Don't care if it fails, only care if it passes
    try {
        if(QUIT == stoi(tokens[0])) {
            std::stringstream ss;
            std::string com;
            ss << QUIT;
            ss >> com;
            this->tokens.command = com;
            valid = true;
        }
    } catch(...) {}
    return valid;
}
bool GameEngine::getDone(){
    return done;
}

bool GameEngine::validTile(std::string tileCode) {
    bool valid = false;
    const char* tile = tileCode.c_str();

    if(tileCode.length() == 2) {
        if(validColour(tile[0]) && validShape(charToInt(tile[1]))) {
            tokens.tileCode = tileCode;
            valid = true;
        }
    }
    return valid;
}

bool GameEngine::validLoc(std::string location) {
    bool validRow = false;
    bool validCol = false;
    int col = -1;

    if(location.length() == 2 || location.length() == 3) {
        const char* loc = location.c_str();

        // If doulbe digit coloumn
        if(3 == location.length())  col = doubleDigitCol(location);
        else                        col = charToInt(location[1]);

        // Check valid row
        if(loc[0] >= 'A' && loc[0] <= board.getHeight())
            validRow = true;

        // Check valid column
        if(col > 0 && col <= board.getWidth())
            validCol = true;
    }
    return validRow && validCol;
}

bool GameEngine::validColour(char c) {
    bool valid = true;

    if     (c == RED);
    else if(c == ORANGE);
    else if(c == YELLOW);
    else if(c == GREEN);
    else if(c == BLUE);
    else if(c == PURPLE);
    else    valid = false;

    return valid;
}

bool GameEngine::validShape(int shape) {
    bool valid = true;

    if     (shape == CIRCLE);
    else if(shape == STAR_4);
    else if(shape == DIAMOND);
    else if(shape == SQUARE);
    else if(shape == STAR_6);
    else if(shape == CLOVER);
    else    valid = false;

    return valid;
}

bool GameEngine::save() {
    bool success = false;
    std::ofstream outputFile("./" + tokens.saveFile + ".save");
    
    if(outputFile.good()) {
        outputFile << player1;
        outputFile << player2;
        outputFile << player3;
        outputFile << board;
        outputFile << tileBag;
        outputFile << currentPlayer->getName();
        success = true;
    }
    return success; 
}

void GameEngine::shuffleTiles(Tile* tiles) {
    //loop throught the whole tile size
    std::random_device randomSeed;
    std::uniform_int_distribution<int> uniform_dist(0, MAX_TILE_BAG_SIZE - 1);
    
    bool stop = false;

    //loop throught the whole tile size
    while(!stop) {
        int randIndex = uniform_dist(randomSeed);
        if(randIndex < temptileBag.size()){
            Tile* t = new Tile(temptileBag.at(randIndex)->colour,temptileBag.at(randIndex)->shape);
            tileBag.push_back(t);
            temptileBag.remove(randIndex);

        }
        if(temptileBag.size() == 0){
            
            stop = true;
        }
    }
}

void GameEngine::createTileBag() {
    // loop through each color and the each shape for it
    // loop through the array of colors and shapes
    Colour c[6] = {RED,ORANGE,YELLOW,GREEN,BLUE,PURPLE};
    Shape  s[6] = {CIRCLE,STAR_4,DIAMOND,SQUARE,STAR_6,CLOVER};
    
    for(int k = 0; k < 2; k++){

        for(int i = 0; i < 6; i++) {

            for(int j = 0; j < 6; j++) {

                Tile* tempTile = new Tile(c[i], s[j]);
                tilesState.push_back(tempTile);
                temptileBag.push_back(tempTile);

            }
        }
    }
    
}

