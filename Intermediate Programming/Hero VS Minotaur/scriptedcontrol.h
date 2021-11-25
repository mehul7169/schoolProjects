#ifndef SCRIPTEDCONTROL_H
#define SCRIPTEDCONTROL_H

#include <vector>
#include "entitycontroller.h"

// An EntityController suitable for scripting (playing a specified
// series of Directions when asked for moves).  Intended to
// allow testing of Game functionality from unit tests.
class ScriptedControl : public EntityController {
private:
  std::vector<Direction> m_input;
  int m_next;

  // copy constructor and assignment operator disallowed
  ScriptedControl(const ScriptedControl &);
  ScriptedControl &operator=(const ScriptedControl &);

public:
  ScriptedControl();
  virtual ~ScriptedControl();

  void setInput(const std::vector<Direction> &input);

  Direction getMoveDirection(Game *game, Entity *entity);
  bool isUser() const;
};

#endif // SCRIPTEDCONTROL_H
