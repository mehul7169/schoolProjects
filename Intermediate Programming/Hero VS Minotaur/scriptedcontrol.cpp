#include <cassert>
#include "scriptedcontrol.h"

ScriptedControl::ScriptedControl() : m_next(0) {
}

ScriptedControl::~ScriptedControl() {
}

void ScriptedControl::setInput(const std::vector<Direction> &input) {
  m_input = input;
}

Direction ScriptedControl::getMoveDirection(Game *, Entity *) {
  assert(m_next < (int) m_input.size());
  Direction dir = m_input[m_next];
  m_next++;
  return dir;
}

bool ScriptedControl::isUser() const {
  return false;
}
