
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
}

bool operator==(const Tile t1, const Tile t2) {
   return t1.colour == t2.colour && t1.shape == t2.shape;
}