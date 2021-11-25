#ifndef INANIMATE_H
#define INANIMATE_H

#include "entitycontroller.h"

// EntityController for inanimate objects.
// Such objects never move on their own, so getMoveDirection should always
// return Direction::NONE.  Such objects *can* be pushed by other
// (animate) Entity objects.
class Inanimate : public EntityController {
private:
  // copy constructor and assignment operator are disallowed
  Inanimate(const Inanimate &);
  Inanimate &operator=(const Inanimate &);

public:
  Inanimate();
  virtual ~Inanimate();

  // Return a Direction specifying the direction in which
  // specified Entity should try to move. In this case, none.
  virtual Direction getMoveDirection(Game *game, Entity *entity);

  // Return true if this EntityController is controlled by
  // user input. EntityControllers other than UIControl should
  // return false. Thus, this returns false.
  virtual bool isUser() const;
};

#endif // INANIMATE_H
