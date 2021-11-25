#ifndef ASTARCHASEHERO_H
#define ASTARCHASEHERO_H

#include "entitycontroller.h"

class AStarChaseHero : public EntityController {
private:
  // copy constructor and assignment operator are disallowed
  AStarChaseHero(const AStarChaseHero &);
  AStarChaseHero &operator=(const AStarChaseHero &);

public:
  AStarChaseHero();
  virtual ~AStarChaseHero();
 
  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;
};

#endif // ASTARCHASEHERO_H
