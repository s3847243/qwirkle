
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include <string>
#include <cmath>
#include "Tile.h"
#include "Util.h"

#define MAX_TILE_BAG_SIZE  72
#define BOARD_SIZE         26
#define COLUMNS            26
#define ROWS              'Z'
#define ROWS_INT       'Z' - 'A'

class Board {
   
public:
   Board();
   
   // Add tile to board
   void addToBoard(Tile* t, int x, int y);

   // Calculate score from previous move - adds score for rows, column and qwirkle
   int calcScoreFrom(int x, int y);

   // Checks game rules for legal move
   bool legalPlacementAt(int x, int y, Tile* t);

   // Display board to standard out
   void displayBoard();  

   // get a tile from board, used to make Board a proper ADT
   Tile* getAt(int x, int y) const;

   int getWidth() const;
   int getHeight() const;

private:
   std::vector<std::vector<Tile*>> board;
   bool firstTilePlaced;
   int width;
   int height;

   // Check, vertically, for illegal moves according to game rules
   bool isLegalVerticalCheck(Tile* comparingTo, int startX, int startY,
                             int lower, int upper);

   // Check, horizontally, for illegal moves according to game rules
   bool isLegalHorizontalCheck(Tile* comparingTo, int startX, int startY,
                               int lower, int upper);
   
   // Update booleans for legality of placement
   // If the tile differs in both colour and shape than that of the tiles already
   // in line, it is illegal. Likewise if it the tile is already present
   void checkConditions(Tile* placingTile, Tile* comparingTo,
                        bool& diffColour, bool& diffShape, bool& sameTile);

   // checks whether tile is placed in a ine
   bool hasAdjacent(int x, int y, int xLow, int xHigh, int yLow, int yHigh);
};

// Print board in file saving format
std::ostream& operator<<(std::ostream &out, const Board& board);

#endif // ASSIGN2_BOARD_H