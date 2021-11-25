#include "chasehero.h"
#include "entitycontroller.h"
#include "game.h"
#include "entity.h"
#include "position.h"
#include <vector>
#include "gamerules.h"
using std::vector;

ChaseHero::ChaseHero() {}

ChaseHero::~ChaseHero() {}

// Return a Direction specifying the direction in which                                         
// specified Entity should try to move. In this case, none.                                     
Direction ChaseHero::getMoveDirection(Game *game, Entity *entity) {
  //Finds closest hero
  vector<Entity *> entities = game->getEntities();
  int minDist = 10000000;
  Entity * closestEntity;
  for (int i = 0; i < (int) entities.size(); i++) {
    Position entityPos = entities[i]->getPosition();
    if (entities[i]->hasProperty('h') && entityPos.distanceFrom(entity->getPosition()) < minDist) {
      closestEntity = entities[i];
      minDist = entityPos.distanceFrom(entity->getPosition());
    }
  }

  //Checks whether closer in horizontal or vertical
  Position heroPos = closestEntity->getPosition();
  int heroX = heroPos.getX();
  int heroY = heroPos.getY();
  int minoX = entity->getPosition().getX();
  int minoY = entity->getPosition().getY();

  int xDiff = heroX - minoX;
  int yDiff = heroY - minoY;
  //test Horizontal right


  if(xDiff == 0 && yDiff == 0) {
    return Direction::NONE;
  }

  if(xDiff == 0) {
    return moveVertically(yDiff, game, entity, minoX, minoY);
  }

  else if (yDiff == 0) {
    return moveHorizontally(xDiff, game, entity, minoX, minoY);
  }

  else if (abs(xDiff) >= abs(yDiff) && xDiff > 0) {
    if (game->getGameRules()->allowMove(game, entity, entity->getPosition(), {minoX + 1, minoY})) 
    return Direction::RIGHT;
    else {
      return moveVertically(yDiff, game, entity, minoX, minoY);
    }
  }

  //t&dest Horizontal left
  else if (abs(xDiff) >= abs(yDiff) && xDiff < 0) {
    if (game->getGameRules()->allowMove(game, entity, entity->getPosition(), {minoX - 1, minoY})) {
      return Direction::LEFT;
    }
    else {
      return moveVertically(yDiff, game, entity, minoX, minoY);
    }
  }

  //t&dest vertical up
  else if (abs(xDiff) < abs(yDiff) && yDiff > 0) {
    if (game->getGameRules()->allowMove(game, entity, entity->getPosition(), {minoX, minoY + 1})) {
      return Direction::DOWN;
    }
    else {
      return moveHorizontally(xDiff, game, entity, minoX, minoY);
    }
  }

  //t&dest vertical down
  else if (abs(xDiff) < abs(yDiff) && yDiff < 0) {
    if (game->getGameRules()->allowMove(game, entity, entity->getPosition(), {minoX, minoY - 1})) {
      return Direction::UP;
    }
    else {
      return moveHorizontally(xDiff, game, entity, minoX, minoY);
    }
  }
  return Direction::NONE;  

}

Direction ChaseHero::moveVertically(int yDiff, Game * game, Entity * entity, int minoX, int minoY) {
  if (yDiff > 0) {
    if (game->getGameRules()->allowMove(game, entity, entity->getPosition(), {minoX, minoY + 1})) {
      return Direction::DOWN;
    }
  } else {
    if (game->getGameRules()->allowMove(game, entity, entity->getPosition(), {minoX, minoY - 1})) {
      return Direction::UP;
    }
  }
  return Direction::NONE;
}

Direction ChaseHero::moveHorizontally(int xDiff, Game * game, Entity * entity, int minoX, int minoY) {
  if (xDiff > 0) {
    if (game->getGameRules()->allowMove(game, entity, entity->getPosition(), {minoX + 1, minoY})) {
      return Direction::RIGHT;
    }
  } else {
    if (game->getGameRules()->allowMove(game, entity, entity->getPosition(), {minoX - 1, minoY})) {
      return Direction::LEFT;
    }
  }
  return Direction::NONE;
}

// Return true if this EntityController is controlled by                                        
// user input. EntityControllers other than UIControl should                                    
// return false. Thus, this returns false.
bool ChaseHero::isUser() const {
  return false;
}
