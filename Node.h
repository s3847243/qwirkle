
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:

   Node(Tile* tile, Node* next);

   // Shallow copy of a Node
   Node(Node& other);

   ~Node();

   // Node data
   Tile* tile;

   // Next node in LinkedList
   Node* next;
};

#endif // ASSIGN2_NODE_H
