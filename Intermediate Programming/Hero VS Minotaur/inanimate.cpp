#include "inanimate.h"
#include "entitycontroller.h"

// EntityController for inanimate objects.                                                        
// Such objects never move on their own, so getMoveDirection should always                        
// return Direction::NONE.  Such objects *can* be pushed by other                                
// (animate) Entity objects.

Inanimate::Inanimate() {}

Inanimate::~Inanimate() {}

// Return a Direction specifying the direction in which
// specified Entity should try to move. In this case, none.
Direction Inanimate::getMoveDirection(Game *, Entity *) {
  return Direction::NONE;
}

// Return true if this EntityController is controlled by
// user input. EntityControllers other than UIControl should
// return false. Thus, this returns false.
bool Inanimate::isUser() const {
  return false;
}
