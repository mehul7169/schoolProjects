#include <stdexcept>
#include "wall.h"
#include "floor.h"
#include "goal.h"
#include "mysterytile.h"
#include "tilefactory.h"

TileFactory::TileFactory() {
}

TileFactory::~TileFactory() {
}

TileFactory *TileFactory::getInstance() {
  static TileFactory theInstance;
  return &theInstance;
}

Tile *TileFactory::createFromChar(char c) {
  switch (c) {
  case '.':
    return new Floor();
  case '#':
    return new Wall();
  case '<':
    return new Goal();
  case 'm':
    return new MysteryTile();
  default:
    // not a valid character
    return nullptr;
  }
}