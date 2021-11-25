#include <sstream>
#include "tctestpp.h"
#include "position.h"
#include "tile.h"
#include "maze.h"
#include "entity.h"
#include "scriptedcontrol.h"
#include "chasehero.h"
#include "textui.h"
#include "basicgamerules.h"
#include "game.h"
#include "ecfactory.h"
#include <iterator>
#include <vector>
#include <fstream>

int main(int argc, char *argv[]) {
  const char *filename;
  if (argc < 2) {
    std::cerr << "Error: Need filename" << std::endl;
    return 1;
  }
  filename = argv[1];

  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cerr << "Error: Could not open maze file" << std::endl;
    return 1;
  }

  Game *game = Game::loadGame(in);
  if (!game) {
    std::cerr << "Error: Invalid game file" << std::endl;
    return 1;
  }

  game->setUI(new TextUI());
  game->setGameRules(new BasicGameRules());
  game->gameLoop();

  delete game;

  return 0;
}
