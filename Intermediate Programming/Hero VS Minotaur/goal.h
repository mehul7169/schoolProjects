#ifndef GOAL_H
#define GOAL_H

#include "tile.h"

// The hero wins the game ifa they reach a Goal tile.
class Goal : public Tile {
private:
  // copy constructor and assignment operator disallowed
  Goal(const Goal &);
  Goal &operator=(const Goal &);

public:
  Goal();
  virtual ~Goal();

  virtual MoveResult checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const;
  virtual bool isGoal() const;
  virtual std::string getGlyph() const;
};

#endif // GOAL_H
