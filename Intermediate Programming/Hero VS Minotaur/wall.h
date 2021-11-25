#ifndef WALL_H
#define WALL_H

#include "tile.h"

// A Wall is a tile that no Entity can move onto
class Wall : public Tile {
private:
  // copy constructor and assignment operator are disallowed
  Wall(const Wall &);
  Wall &operator=(const Wall &);

public:
  Wall();
  virtual ~Wall();

  virtual MoveResult checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const;
  virtual bool isGoal() const;
  virtual std::string getGlyph() const;
};

#endif // WALL_H
