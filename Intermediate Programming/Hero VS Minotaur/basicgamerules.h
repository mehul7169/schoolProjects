#ifndef BASICGAMERULES_H
#define BASICGAMERULES_H

#include "gamerules.h"

class BasicGameRules : public GameRules {
private:
  // copy constructor and assignment operator are disallowed
  BasicGameRules(const BasicGameRules &);
  BasicGameRules &operator=(const BasicGameRules &);

public:
  BasicGameRules();
  virtual ~BasicGameRules();

  virtual bool allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const;
  virtual void enactMove(Game *game, Entity *actor, const Position &dest) const;
  virtual GameResult checkGameResult(Game *game) const;

private:
  bool checkCollision(Game *game, Entity *actor, Entity *player) const ;
  bool checkTileMove(Game *game, Position dest, Position source, Entity *actor) const ;
  Position getPushPosition(Position actorPosition, Position playerPosition) const ;
};

#endif // BASICGAMERULES_H
