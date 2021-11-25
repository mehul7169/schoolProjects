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
#include "uicontrol.h"
#include "entitycontroller.h"
#include "astarchasehero.h"
#include <iterator>
#include <vector>

Game::Game(){
}

Game::~Game() {
	delete gameMaze;
	delete gameUI;
	delete simpGameRules;
}

void Game::setMaze(Maze *maze) {
	gameMaze = maze;
}

void Game::setUI(UI *ui) {
	gameUI = ui;
}

// Set the GameRules object. The Game object assumes responsibility for
// deleting it.
void Game::setGameRules(GameRules *gameRules) {
	simpGameRules = gameRules;
}

// Add an Entity to the sequence of entities. The Game object assumes
// responsibility for deleting it.
void Game::addEntity(Entity *entity){
	allEntities.push_back(entity);
}

// Get the Entity at the specified Position.  Return nullptr if
// there is no Entity at the specified Position.
Entity * Game::getEntityAt(const Position &pos) {
	for (int i = 0; i < (int) allEntities.size(); i++) {
		if (allEntities[i]->getPosition() == pos) {
			return allEntities[i];
		}
	}
	return nullptr;
}

// Get a const reference to the Game object's internal vector
// of pointers to Entity objects.
const Game::EntityVec &Game::getEntities() const {
	return this->allEntities;
}

// Get a vector of pointers to Entity objects that have the
// specified property. The vector could be empty if no Entity objects
// have the specified property.
std::vector<Entity *> Game::getEntitiesWithProperty(char prop) const {
	std::vector<Entity *> propEntities;
	for (int i = 0; i < (int) allEntities.size(); i++) {
		if (allEntities[i]->hasProperty(prop)) {
			propEntities.push_back(allEntities[i]);
		}
	}
	return propEntities;
}

// Get the Maze object.
Maze *Game::getMaze() {
	return this->gameMaze;
}

// Get the UI object.
UI *Game::getUI() {
	return this->gameUI;
}

// Get the GameRules object.
GameRules *Game::getGameRules() {
	return this->simpGameRules;
}

// Let the Entity objects take turns in round-robin fashion until
// the GameRules object determines that the hero has won or lost.
// Should call the render member function on the UI object just before
// an Entity whose EntityController is controlled by the user takes
// a turn.
void Game::gameLoop() {
//while loop for game result
//check all entities

	while (Game::simpGameRules->checkGameResult(this) == GameResult::UNKNOWN) {
		for(int i = 0; i < (int) this->allEntities.size(); i++) {
			if (allEntities[i]->hasProperty('h')) {
				Game::gameUI->render(this);
			}
			takeTurn(allEntities[i]);
		}
	}
	if (Game::simpGameRules->checkGameResult(this) == GameResult::HERO_LOSES){
		Game::gameUI->displayMessage(": Hero loses", false);
		Game::gameUI->render(this);
		return;
	} else if (Game::simpGameRules->checkGameResult(this) == GameResult::HERO_WINS){
		Game::gameUI->displayMessage(": Hero wins", false);
		Game::gameUI->render(this);
		return;
	}
}

// Let specified actor Entity take a turn.
// This is public so that it can be called from
// unit tests.  It is mainly intended to be called from
// the gameLoop member function.
void Game::takeTurn(Entity *actor) {
	Direction toMove;
	if (actor->hasProperty('v')) {
		return;
	}
	else {
		EntityController * actorController = actor->getController();
		toMove = actorController->getMoveDirection(this, actor);
	}

	Position const * dest;
	Position actorPosition = actor->getPosition();
	int actorX = actorPosition.getX();
	int actorY = actorPosition.getY();
	
	if (toMove == Direction::UP) {
		dest = new Position(actorX, actorY - 1);
	}
	else if (toMove == Direction::LEFT) {
		dest = new Position(actorX - 1, actorY);
	}
	else if (toMove == Direction::RIGHT) {
		dest = new Position(actorX + 1, actorY);
	}
	else if (toMove == Direction::DOWN) {
		dest = new Position(actorX, actorY + 1);
	}

	if (Game::simpGameRules->allowMove(this, actor, actor->getPosition(), *dest)) {
		Game::simpGameRules->enactMove(this, actor, *dest);
	} else {
		std::cout << ": Illegal move" << std::endl;	
	}
}

// Read initial Game data from the specified istream, and return
// the resulting Game object.
Game *Game::loadGame(std::istream &in) {
	Game * resultGame = new Game();
	resultGame->setMaze(Maze::read(in));
	
	std::string describ;
	std::string glyph;
	std::string property;
	std::string controller;
	int x;
	int y;
	while (in) {
		in >> describ;
		if (in.fail()) {
			break;
		}
		Entity * newEntity = new Entity();
		newEntity -> setGlyph(describ.substr(0,1));
		if (describ.at(1) == 'a') {
			AStarChaseHero * cleverAI = new AStarChaseHero();
			newEntity->setController(cleverAI);
		} else if (describ.at(1) == 'c') {
			ChaseHero * AI = new ChaseHero();
			newEntity->setController(AI);
		} else if (describ.at(1) == 'u') {
			UIControl * userControl = new UIControl();
			newEntity->setController(userControl);
		}
		newEntity->setProperties(describ.substr(2,1));
		in >> x >> y;
		Position * entPos = new Position(x, y);
		newEntity->setPosition(*entPos);
		resultGame->addEntity(newEntity);
	}
	return resultGame;
}
