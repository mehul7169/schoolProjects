#include "position.h"
#include "astarchasehero.h"
#include "game.h"
#include "entity.h"
#include "maze.h"
#include <cstdlib>
#include <map>
#include <set>
#include <bits/stdc++.h>
#include <iterator>
#include "tile.h"

AStarChaseHero::AStarChaseHero() {}
AStarChaseHero::~AStarChaseHero() {}

Direction AStarChaseHero::getMoveDirection(Game *game, Entity *entity) {


  Maze * gameMaze = game->getMaze();
  int width = gameMaze->getWidth();
  int height = gameMaze->getHeight();
  //should use distanceFrom function
  int h_n;

  //the position and its distance
  std::map<Position, int> f_n, g_n;

  //the position and the position just before
  std::map<Position, Position> pathTaken;

  //positions to inspect
  std::set<Position> openSet;

  //positions inspected
  std::set<Position> closedSet;

  std::vector<Entity *> entities = game->getEntities();
  int minDist = INT_MAX;
  Entity * closestEntity;
  
  Position actorPos = entity->getPosition();
  openSet.emplace(actorPos);

  for (int i = 0; i < (int) entities.size(); i++) {
    Position entityPos = entities[i]->getPosition();
    if (entities[i]->hasProperty('h') && entityPos.distanceFrom(entity->getPosition()) < minDist) {
      closestEntity = entities[i];
      minDist = entityPos.distanceFrom(entity->getPosition());
    }
  }

  Position goalPos = closestEntity->getPosition();
  
  Position start = entity->getPosition();
  //Position goal = position(game->width - 3, 1);

  openSet.emplace(start);

  //int hScore = start.distanceFrom(goal);
  g_n.emplace(start, INT_MAX);
  f_n.emplace(start, start.distanceFrom(goalPos));
  /*
  g_n[start] = INT_MAX;
  f_n[start] = start.distanceFrom(goal);
  */
  h_n = start.distanceFrom(goalPos);
  f_n.emplace(start, h_n);
   
  Position ancestor = start;
  //f_n[currNode] = g_n[currNode] + hScore;
  int lowestF = INT_MAX;
  Position lowestPosition;
  while (!openSet.empty()) {
    for (std::set<Position>::iterator it = openSet.begin(); it != openSet.end(); ++it) {
      if (f_n.at(*it) < lowestF) {
	lowestF = f_n.at(*it);
	lowestPosition = *it; /*node at this position*/
      }
    }

    if (lowestPosition == goalPos) {
      pathTaken.emplace(lowestPosition, ancestor);
    }

    openSet.erase(lowestPosition);
    
    Position neighbors[4];
    neighbors[0] = Position(lowestPosition.getX(), lowestPosition.getY() - 1);//up
    neighbors[1] = Position(lowestPosition.getX(), lowestPosition.getY() + 1);//down
    neighbors[2] = Position(lowestPosition.getX() + 1, lowestPosition.getY());//right
    neighbors[3] = Position(lowestPosition.getX() - 1, lowestPosition.getY());//left
    int tentative_gScore = 0; 
    for (int i = 0; i < 4; ++i) {
      if (neighbors[i].inBounds(width, height) && gameMaze->getTile(neighbors[i])->checkMoveOnto(entity, lowestPosition, neighbors[i]) == MoveResult::ALLOW) {
	tentative_gScore = g_n.at(lowestPosition) + lowestPosition.distanceFrom(neighbors[i]);
      }
      
      int distance_gTemp = start.distanceFrom(neighbors[i]);
      g_n.emplace(neighbors[i], distance_gTemp);
      
      if (tentative_gScore < g_n.at(neighbors[i])) {
	pathTaken.at(neighbors[i]) = lowestPosition;
	g_n.at(neighbors[i]) = tentative_gScore;
	f_n.at(neighbors[i]) = g_n.at(neighbors[i]) + neighbors[i].distanceFrom(goalPos);
	if(openSet.find(neighbors[i]) == openSet.end()) {
	  openSet.emplace(neighbors[i]);
	}
      }
      
    }
  }

  Position moveTo = pathTaken.begin()->first;
  Position orig = pathTaken.begin()->second;

  if (moveTo.getX() == orig.getX() && moveTo.getY() > orig.getY()) {
    return Direction::DOWN;
  }

  else if (moveTo.getX() == orig.getX() && moveTo.getY() < orig.getY()) {
    return Direction::UP;
  }

  else if (moveTo.getX() > orig.getX() && moveTo.getY() == orig.getY())	{
    return Direction::RIGHT;
  }

  else if (moveTo.getX() < orig.getX() && moveTo.getY() == orig.getY())	{
    return Direction::LEFT;
  }
  
  return Direction::NONE;
}

  
//not the user, rather the AI that chases the user
bool AStarChaseHero::isUser() const {
  return false;
}


 
