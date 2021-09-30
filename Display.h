
#ifndef ASSIGN2_DISPLAY_H
#define ASSIGN2_DISPLAY_H

#include <string>
#include <regex>
#include "Player.h"
#include "LinkedList.h"
#include "Board.h"
#include "Util.h"

#define NEW_GAME        1
#define LOAD_GAME       2
#define CREDITS         3
#define QUIT            4
#define BACK            5

class Display {
    public:
        Display();

        // Used to set the quit variable in qwirkle.cpp, so as to not print
        // menu again before quitting
        Display(bool* quit);
        // used to print the menu
        void printMenu();
        // used to print the credits

        void printCredits();
        // print help message
        void printHelp();
        // used to print the current Hand

        void printHand(Player& p);
        // used to print the players score and the current turn
        void print(Player& p,Player& p1,Player& p2,Player& p3);
        // used to print the board
        void print(Board& b);
        // used to print the linkedlist
        void print(LinkedList& list);
        // used to print a string
        void print(std::string s);
        // used to print the message before game ends
        void gameOverMessage(Player p1,Player p2,Player p3);

        // Menu selection handling
        int makeSelection();
        std::string getInput();
        void prompt();

    private:
    bool* quit;
};

#endif // ASSIGN2_DISPLAY_H