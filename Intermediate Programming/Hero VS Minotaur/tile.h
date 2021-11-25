#ifndef TILE_H
#define TILE_H

#include <string>

class Position;
class Entity;

// Returned by Tile's checkMoveOnto member function, to report
// whether an Entity can move onto the Tile.
enum class MoveResult {
  ALLOW,
  BLOCK,
};

// A Tile occupies one grid position in a Maze, and determines
// how an Entity object can move at that position.
class Tile {
private:
  // disallow copy constructor and assignment operator
  Tile(const Tile &);
  Tile &operator=(const Tile &);

public:
  Tile();
  virtual ~Tile();

  // Check whether specified Entity is allowed to move from fromPos onto
  // tilePos.  tilePos can be assumed to be Position of this Tile.
  // fromPos is not necessarily the Entity's Position, because this
  // member function could be called as part of pathfinding, where
  // it is important to know where in the Maze the Entity can move,
  // regardless of where it is currently located.
  virtual MoveResult checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const = 0;

  // Return true if this is the goal Tile, false if not.
  virtual bool isGoal() const = 0;

  // Get the glyph representing this Tile. Should be a single character.
  virtual std::string getGlyph() const = 0;
};

#endif // TILE_H
