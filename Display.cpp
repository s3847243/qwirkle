#include <iostream>
#include "Display.h"

Display::Display() {}
Display::Display(bool* quit) : quit(quit) {}

void Display::printMenu() {
    std::cout << "Welcome to Qwirkle"   << std::endl;
    std::cout << "----"                 << std::endl;
    std::cout << "Menu"                 << std::endl;
    std::cout << "----"                 << std::endl;
    std::cout << "1. New Game"          << std::endl;
    std::cout << "2. Load Game"         << std::endl;
    std::cout << "3. Credits"           << std::endl;
    std::cout << "4. Quit"              << std::endl;
    std::cout << "Type 'help' if needed"<< std::endl;
    std::cout << "Type Done when the tiles have been placed" << std::endl;
}

void Display::printCredits() {
    std::cout << "------------------------"                 << std::endl;
    std::cout << "Name: Abu Kuhafah"                        << std::endl;
    std::cout << "Student ID: s3839222"                     << std::endl;
    std::cout << "Email: s3839222@student.rmit.edu.au"      << std::endl;
    std::cout <<                                               std::endl;
    std::cout << "Name: Alasdair Moloney"                   << std::endl;
    std::cout << "Student ID: s3785526"                     << std::endl;
    std::cout << "Email: s3785526@student.rmit.edu.au"      << std::endl;
    std::cout <<                                               std::endl;
    std::cout << "Name: Hibbaan Mohammed Nawaz"             << std::endl;
    std::cout << "Student ID: s3847243"                     << std::endl;
    std::cout << "Email: s3847243@student.rmit.edu.au"      << std::endl;
    std::cout <<                                               std::endl;
    std::cout << "Name: Sithira Deelaka Hikkaduwa Liyanage" << std::endl;
    std::cout << "Student ID: s3820369"                     << std::endl;
    std::cout << "Email: s3820369@student.rmit.edu.au"      << std::endl;
    std::cout << "------------------------"                 << std::endl;
    std::cout <<                                               std::endl;
    std::cout << "5. back"                                  << std::endl;
}

std::string Display::getInput() {
    std::string input;
    while(!*quit && !std::regex_match(input, std::regex("\\w+"))) {
        prompt();
        if(std::getline(std::cin, input).eof()) {
            *quit = true;
            input = QUIT;
        }
    }
    std::cout << std::endl;
    return input;
}

int Display::makeSelection() {
    bool selectionDone = true;
    std::string input = "";

    do {
        input = getInput();

        if(quit);
        else if(input.length() == 1) {
            if     (charToInt(input[0]) == NEW_GAME);
            else if(charToInt(input[0]) == LOAD_GAME);
            else if(charToInt(input[0]) == CREDITS);
            else if(charToInt(input[0]) == QUIT);
            else if(charToInt(input[0]) == BACK);
            else selectionDone = false;
        }
        
        if(!selectionDone)
            print("Please select a valid option.");

   } while(!selectionDone);
   return charToInt(input[0]);
}
void Display::gameOverMessage(Player p1,Player p2,Player p3){
    std::cout << "Game Over" << std::endl;
    std::cout << "Score for " ;
    std::cout << p1.getName() +":";
    std::cout << p1.getScore() << std::endl;
    std::cout << "Score for " ;
    std::cout << p2.getName() +":";
    std::cout << p2.getScore() << std::endl;
    std::cout << "Score for " ;
    std::cout << p3.getName() +":";
    std::cout << p3.getScore() << std::endl;
    if((p1.getScore() >= p2.getScore()) && p1.getScore() >= p3.getScore()){
        std::cout << "Player " + p1.getName() + " won" << std::endl;

    }else if (p2.getScore() >= p1.getScore() && p2.getScore() >= p3.getScore()){
        std::cout << "Player " + p2.getName() + " won" << std::endl;
    }else if (p3.getScore() >= p1.getScore() && p3.getScore() >= p2.getScore() ){
        std::cout << "Player " + p3.getName() + " won" << std::endl;

    }
}

void Display::prompt() {
    std::cout << "> ";
}

void Display::print(std::string s) {
   std::cout << s << std::endl;
}

void Display::print(LinkedList& list) {
    std::cout << list;
}

void Display::print(Player& currentplayer,Player& p1,Player& p2,Player& p3) {
   std::cout << currentplayer.getName() + " ,it your turn" << std::endl;
    std::cout << "Score for " + p1.getName() + ": ";
    std::cout << p1.getScore() << std::endl;
    std::cout << "Score for " + p2.getName() + ": ";
    std::cout << p2.getScore() << std::endl;
    std::cout << "Score for " + p3.getName() + ": ";
    std::cout << p3.getScore() << std::endl;
}
void Display::printHand(Player& p){
    std::cout<< "your hand is"<<std::endl;
    std::cout << p.getHand() << std::endl;
}

std::ostream& operator<<(std::ostream &out, const LinkedList& list) {
    for(int i = 0; i < list.size(); ++i) {
        out << list.at(i)->colour << list.at(i)->shape;
        if(i != list.size()-1)
            out << ",";
    }
    out << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream &out, const Player& player) {
    out << player.getName() << '\n' << std::to_string(player.getScore())
        << '\n' << player.getHandConst();
    return out;
}

void Display::print(Board& board) {
    char alphabets = 'A';
    std::cout << "\n  ";

    for(int y = 0; y < 2; y++) {
        for(int u = 1; u < BOARD_SIZE + 1; u++) {
            if(y == 0) {
                if(u <= 9)
                    std::cout << "0";
                std::cout << u << " ";
            }
            else {
                std::cout << "---";
            }
        }
        if(y == 1)
            std::cout << "--";
        std::cout << std::endl;
    }
    for(int row = 0; row < BOARD_SIZE; ++row) {

        for(int c = 0; c < BOARD_SIZE; c++) {
            if(c == 0) {
                std::cout << alphabets << "|";
                alphabets++;
            }
            if(board.getAt(c, row) == nullptr) {
                std::cout << "  |";
            } else {
                std::cout << board.getAt(c, row)->colour
                          << board.getAt(c, row)->shape << "|";
            }
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}


std::ostream& operator<<(std::ostream &out, const Board& board) {
    out << board.getWidth() << ',' << ROWS_INT + 1 << '\n';

    for(int i = 0; i < ROWS_INT + 1; ++i) {

        for(int j = 0; j < COLUMNS; ++j) {
            Tile* tile = board.getAt(j, i);

            if(nullptr != tile)
                out << *tile << '@' << (char)(i + 'A') << j+1 << ' ';
        }
    }
    out << '\n';
     return out;
}

std::ostream& operator<<(std::ostream &out, const Tile& tile) {
    out << tile.colour << tile.shape;
    return out;
}

void Display::printHelp(){
    std::cout << "1. To place a tile type 'place  at'"<< std::endl;
    std::cout << "2. To replace a tile type replace "<< std::endl;
    std::cout << "3. To quit type 4                 "<< std::endl;
    std::cout << "4. You can place a tile mutiple times"<< std::endl;
    std::cout << "5. type 'done' when you've finished placing tiles"<< std::endl;
    std::cout << "6. type skip if you dont want to place any tiles"<< std::endl;
    std::cout << "7. to save the game type the command 'save' "<< std::endl;
    std::cout << "8. you can print the credits by typing 3 at the menu "<< std::endl;
}