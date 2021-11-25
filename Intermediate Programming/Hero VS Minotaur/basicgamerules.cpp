#include "basicgamerules.h"
#include "gamerules.h"
#include "tile.h"
#include "game.h"
#include "position.h"
#include "uicontrol.h"
#include "entity.h"
#include "maze.h"

BasicGameRules::BasicGameRules() {
}

BasicGameRules::~BasicGameRules() {
}

bool BasicGameRules::allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const {
	Maze * mazeGame = game->getMaze();
	if (mazeGame->inBounds(dest)) {
		int distance = source.distanceFrom(dest);
		if (distance <= 1) {
			Entity * player = game->getEntityAt(dest);
			if (player != nullptr) {
				return (!this->checkCollision(game, actor, player));
			}
			else {
				const Tile * tileAtDest = mazeGame->getTile(dest);
				if (tileAtDest->checkMoveOnto(actor, source, dest) == MoveResult::ALLOW) {
					return true;
				}
			} 
		}
	}
	return false;
}

void BasicGameRules::enactMove(Game *game, Entity *actor, const Position &dest) const {
	
		Entity * entityDest = game->getEntityAt(dest);
		if (entityDest != nullptr && entityDest->hasProperty('v')) {
			Position moveDest = BasicGameRules::getPushPosition(actor->getPosition(), entityDest->getPosition());
			entityDest->setPosition(moveDest);
		}
		actor->setPosition(dest);
}

GameResult BasicGameRules::checkGameResult(Game *game) const {
	std::vector<Entity *> heroes = game->getEntitiesWithProperty('h');
	std::vector<Entity *> minotaurs = game->getEntitiesWithProperty('m');
	Maze * gameMaze = game->getMaze();
	for (int i = 0; i < (int) heroes.size(); i++) {
		for (int j = 0; j < (int) minotaurs.size(); j++) {
			if (heroes[i]->getPosition().getX() == minotaurs[j]->getPosition().getX() && 
				heroes[i]->getPosition().getY() == minotaurs[j]->getPosition().getY()) {
				return GameResult::HERO_LOSES;
			}
		}
	}
	for (int i = 0; i < (int) heroes.size(); i++) {
		const Tile * getTile = gameMaze->getTile(heroes[i]->getPosition());
		if (getTile->isGoal()) {
			return GameResult::HERO_WINS;
		}
	}
	return GameResult::UNKNOWN;
	
}

bool BasicGameRules::checkCollision(Game *game, Entity *actor, Entity *player) const {
	if (player->hasProperty('v')) {
		Position playerDest = BasicGameRules::getPushPosition(actor->getPosition(), player->getPosition());
		Maze * mazeGame = game->getMaze();
		if(mazeGame->inBounds(playerDest) && BasicGameRules::checkTileMove(game, playerDest, player->getPosition(), actor)) {
			return false;
		}
		else {
			return true;
		}	
	}
	if ((player->hasProperty('h') && actor->hasProperty('m')) ||
        (player->hasProperty('m') && actor->hasProperty('h'))) {
			return false;
	}		
	return true;
}

bool BasicGameRules::checkTileMove(Game *game, Position dest, Position source, Entity *actor) const {
	Maze * mazeGame = game->getMaze();
	Tile const * destTile = mazeGame->getTile(dest);
	return (destTile->checkMoveOnto(actor, source, dest) == MoveResult::ALLOW);
}

Position BasicGameRules::getPushPosition(Position actorPosition, Position playerPosition) const {
	int actorX = actorPosition.getX();
	int actorY = actorPosition.getY();
	int playerX = playerPosition.getX();
	int playerY = playerPosition.getY();
	int changeX = playerX - actorX;
	int changeY = playerY - actorY;
	Position result(playerX + changeX, playerY + changeY);
	return result;
}