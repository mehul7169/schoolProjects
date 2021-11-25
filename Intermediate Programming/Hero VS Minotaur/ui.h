#ifndef UI_H
#define UI_H

#include <string>
#include "position.h"

class Game;

// UI (User Interface) has virtual member functions to
// display information to the user (displayMessage, render)
// and to get user input to determine the requested move
// direction for a controlled Entity (getMoveDirection).
// It is a singleton: only one UI object can be created,
// and the getInstance static member function can be called
// to get a pointer to the singleton instance.
class UI {
private:
  // pointer to singleton instance of UI
  static UI *s_instance;

  // copy constructor and assignment operator disallowed
  UI(const UI &);
  UI &operator=(const UI &);

public:
  UI();
  virtual ~UI();

  static UI *getInstance();

  // get requested move direction
  virtual Direction getMoveDirection() = 0;

  // send a one-line message to be displayed the next time
  // the render member function is called; if endgame parameter is
  // true, it will be the last message displayed because the game
  // is over
  virtual void displayMessage(const std::string &msg, bool endgame = false) = 0;

  // render the UI (draw maze and entities, any posted UI message)
  virtual void render(Game *game) = 0;
};

#endif // UI_H
