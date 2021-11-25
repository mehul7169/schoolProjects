#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include "position.h"

class Game;
class Entity;

class EntityController {
private:
  // copy constructor and assignment operator disallowed
  EntityController(const EntityController &);
  EntityController &operator=(const EntityController &);

public:
  EntityController();
  virtual ~EntityController();

  // Return a Direction specifying the direction in which
  // specified Entity should try to move.
  virtual Direction getMoveDirection(Game *game, Entity *entity) = 0;

  // Return true if this EntityController is controlled by
  // user input. EntityControllers other than UIControl should
  // return false.
  virtual bool isUser() const = 0;
};

#endif // ENTITYCONTROLLER_H
