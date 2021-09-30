
#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include <string>


#include "LinkedList.h"
#include "Display.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"
#include "TileCodes.h"

#define MAX_ARGS        4
#define PLACE        "place"
#define DONE          "done"
#define REPLACE     "replace"
#define SAVE         "save"
#define HELP         "help"
#define AT            "at"
#define NO_ERROR       ""
#define SKIP           "skip"

class GameEngine {
    public:
        GameEngine();
        GameEngine(std::string player1Name, std::string player2Name,std::string player3Name);
        ~GameEngine();
        void start();

    private:
        std::string errorMessage;
        
        // Parsed tokens of the command form stdandard in
        typedef struct
        {
            std::string command;
            std::string tileCode;
            std::string boardLoc;
            std::string saveFile;
        } Tokens_t;
        Tokens_t tokens;
        Display display;
        LinkedList tileBag;
        LinkedList temptileBag;
        Player* currentPlayer;
        Player player1;
        Player player2;
        Player player3;
        Board board;

        std::vector<Tile*> tilesState;
        bool done;

        // Parse standard in command syntax. Checks bounds of board, valid command,
        // valid tile
        bool parseInput(std::string input);
        // checks if done has been written 
        bool getDone();
        // Validate tile from input
        bool validTile(std::string tileCode);

        // Validate tile colour from input
        bool validColour(char colour);

        // Validate tile shape from input
        bool validShape(int shape);

        // Validate board location from input
        bool validLoc(std::string location);

        // Perform a valid command - place, replace, save
        bool executeCommand(bool* quit);

        // Checks end game condition
        bool gameIsOver();

        // Checks if error is set, prints
        void checkError();

        // Save game state to file
        bool save();


        void createTileBag();

        //void shuffleTiles(std::vector<Tile*> tiles);

        void shuffleTiles(Tile * tiles);
};

#endif // ASSIGN2_GAMEENGINE_H