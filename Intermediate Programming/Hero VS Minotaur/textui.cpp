#include "textui.h"
#include "position.h"
#include "maze.h"
#include "game.h"
#include "tile.h"
#include "entity.h"
#include <iostream>

TextUI::TextUI() {}

TextUI::~TextUI(){}

Direction TextUI::getMoveDirection() {

  //store the move input by the user, string for compare function
  char move;
  bool validMove = true;

  //while move entered not valid, continue iteration
  
  do {
    std::cout << "Your move (u/d/l/r): ";
    std::cin >> move;
    if (move == 'u') {
      return Direction::UP;
    } else if (move == 'd') {
      return Direction::DOWN;
    } else if (move == 'l') {
      return Direction::LEFT;
    } else if (move == 'r') {
      return Direction::RIGHT;
    } else {
      std::cout << "Unknown direction" << std::endl;
      validMove = false;
    }
  } while (!validMove);

  //no direction specified
  return Direction::NONE;
}

void TextUI::displayMessage(const std::string &msg, bool endgame) {

  //store inside the gameMessage field
  if (endgame != true) {
    gameMessage = msg;
  } else {
    gameMessage = "\0";
  }
}

void TextUI::render(Game *game) {
  Maze* mazeGame = game->getMaze();
  int width = mazeGame->getWidth();
  int height = mazeGame->getHeight();
  int count;

  std::vector<Entity *> allEntities = game->getEntities();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {      
      const Position* current = new Position(x, y);
      count = 0;
      for (int i = 0; i < (int) allEntities.size(); i++) {
        if (allEntities[i]->getPosition().getX() == x && allEntities[i]->getPosition().getY() == y) {
          std::cout << allEntities[i]->getGlyph();
          count++;
        }
      }
      if (count == 0) {
        std::cout << (mazeGame ->getTile(*current))->getGlyph(); 
      }
    }
    std::cout << std::endl;
  }
  if (gameMessage != "\0") {
    std::cout << gameMessage << "\n";
    gameMessage = "\0";
  }
}
