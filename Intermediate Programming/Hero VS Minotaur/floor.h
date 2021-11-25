#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"

// A Floor tile is one that any Entity can move onto (or be pushed onto)
class Floor : public Tile {
private:
  // copy constructor and assignment operator are disallowed
  Floor(const Floor &);
  Floor &operator=(const Floor &);

public:
  Floor();
  virtual ~Floor();

  virtual MoveResult checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const;
  virtual bool isGoal() const;
  virtual std::string getGlyph() const;
};

#endif // FLOOR_H
