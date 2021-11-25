#ifndef MYSTERYCONTROLLER_H
#define MYSTERYCONTROLLER_H

#include "entitycontroller.h"

class MysteryController : public EntityController {
private:
  // copy constructor and assignment operator disallowed
  MysteryController(const MysteryController &);
  MysteryController &operator=(const MysteryController &);

public:
  MysteryController();
  virtual ~MysteryController();

  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;
};

#endif // MYSTERYCONTROLLER_H
