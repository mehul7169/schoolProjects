#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>

class Maze;
class UI;
class Position;
class Entity;
class GameRules;

// The Game class encapsulates all of the game state, and coordinates
// the overall gameplay.
class Game {
public:
  // Typedef to refer to a vector of pointers to Entity objects
  typedef std::vector<Entity *> EntityVec;

private:
  Maze * gameMaze;
  EntityVec allEntities;
  UI * gameUI;
  GameRules * simpGameRules;


  // disallow copy constructor and assignment operator
  Game(const Game &);
  Game &operator=(const Game &);

public:
  Game();
  //destructor releases all memory
  ~Game();

  // Set the Maze object. The Game object assumes responsibility for
  // deleting it.
  void setMaze(Maze *maze);

  // Set the UI object. The Game object assumes responsibility for
  // deleting it.
  void setUI(UI *ui);

  // Set the GameRules object. The Game object assumes responsibility for
  // deleting it.
  void setGameRules(GameRules *gameRules);

  // Add an Entity to the sequence of entities. The Game object assumes
  // responsibility for deleting it.
  void addEntity(Entity *entity);

  // Get the Entity at the specified Position.  Return nullptr if
  // there is no Entity at the specified Position.
  Entity *getEntityAt(const Position &pos);

  // Get a const reference to the Game object's internal vector
  // of pointers to Entity objects.
  const std::vector<Entity *> &getEntities() const;

  // Get a vector of pointers to Entity objects that have the
  // specified property. The vector could be empty if no Entity objects
  // have the specified property.
  std::vector<Entity *> getEntitiesWithProperty(char prop) const;

  // Get the Maze object.
  Maze *getMaze();

  // Get the UI object.
  UI *getUI();

  // Get the GameRules object.
  GameRules *getGameRules();

  // Let the Entity objects take turns in round-robin fashion until
  // the GameRules object determines that the hero has won or lost.
  // Should call the render member function on the UI object just before
  // an Entity whose EntityController is controlled by the user takes
  // a turn.
  void gameLoop();

  // Let specified actor Entity take a turn.
  // This is public so that it can be called from
  // unit tests.  It is mainly intended to be called from
  // the gameLoop member function.
  void takeTurn(Entity *actor);

  // Read initial Game data from the specified istream, and return
  // the resulting Game object.
  static Game *loadGame(std::istream &in);

private:
  // Add your private member functions here...
};

#endif // GAME_H
