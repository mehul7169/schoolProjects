#ifndef MYSTERYTILE_H
#define MYSTERYTILE_H

#include "tile.h"

class MysteryTile : public Tile {
private:
  // copy constructor and assignment operator disallowed
  MysteryTile(const MysteryTile &);
  MysteryTile &operator=(const MysteryTile &);

public:
  MysteryTile();
  virtual ~MysteryTile();

  virtual MoveResult checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const;
  virtual bool isGoal() const;
  virtual std::string getGlyph() const;
};

#endif // MYSTERYTILE_H
