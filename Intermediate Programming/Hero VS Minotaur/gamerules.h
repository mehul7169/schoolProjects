#ifndef GAMERULES_H
#define GAMERULES_H

#include "game.h"
class Entity;
class Position;

enum class GameResult {
  // game is not over yet
  UNKNOWN,
  // game over, hero wins
  HERO_WINS,
  // game over, hero loses (captured by monster)
  HERO_LOSES
};

// A GameRules object determines which moves are legal,
// carries out legal moves, determines whether or not
// the game is over, and (if the game is over) determines
// whether the hero won or lost.
class GameRules {
private:
  // copy constructor and assignment operator are disallowed
  GameRules(const GameRules &);
  GameRules &operator=(const GameRules &);

public:
  GameRules();
  virtual ~GameRules();

  // Check whether specified Entity (the actor) is allowed to move
  // from the specified source Position to the specified destination Position.
  // Note that the source position is not necessarily the actor's Position,
  // because this function could be called in pathfinding to evaluate
  // a hypothetical move.
  virtual bool allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const = 0;

  // Carry out the move of specified Entity (the actor) to the
  // specified destination Position.  This should only be called
  // if allowMove returned true.
  virtual void enactMove(Game *game, Entity *actor, const Position &dest) const = 0;

  // Check the Game state to determine the GameResult
  virtual GameResult checkGameResult(Game *game) const = 0;
};

#endif // GAMERULES_H
