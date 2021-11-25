#ifndef POSITION_H
#define POSITION_H

#include <stdexcept>
#include <iostream>

// Directions for Entity movement
enum class Direction {
  UP, DOWN, LEFT, RIGHT, NONE,
};

// A Position object represents an x,y coordinate within a Maze.
// Note that Position objects have value semantics (meaning that they
// can be copied and assigned.)  Also note that Position objects
// have a < operator (less than), so they can be stored in sets
// and used as keys in maps.
class Position {
private:
  int x, y;

public:
  // Default constructor
  Position() : x(0), y(0) {
  }

  // Constructor from x/y coordinates
  Position(int x, int y) : x(x), y(y) {
  }

  // Copy constructor
  Position(const Position &other) : x(other.x), y(other.y) {
  }

  // Destructor
  ~Position() {
  }

  // Assignment operator
  Position& operator=(const Position &rhs) {
    if (this != &rhs) {
      x = rhs.x;
      y = rhs.y;
    }
    return *this;
  }

  // Get the Position's x coordinate
  int getX() const {
    return x;
  }

  // Get the Position's y coordinate
  int getY() const {
    return y;
  }

  // Return the Position that is displaced by moving 1 step
  // in the specified direction.  This function is useful for
  // carrying out moves, or evaluating hypothetical moves.
  Position displace(Direction dir) const {
    switch (dir) {
    case Direction::UP:
      return Position(x, y - 1);
    case Direction::DOWN:
      return Position(x, y + 1);
    case Direction::LEFT:
      return Position(x - 1, y);
    case Direction::RIGHT:
      return Position(x + 1, y);
    case Direction::NONE:
      return *this;
    }
    throw std::runtime_error("Unknown direction");
  }

  // Get the distance from this Position to specified Position,
  // measured by the number of up/down/left/right steps.
  int distanceFrom(const Position &other) const {
    int xdiff = x - other.x;
    int ydiff = y - other.y;
    if (xdiff < 0) { xdiff = -xdiff; }
    if (ydiff < 0) { ydiff = -ydiff; }
    return xdiff + ydiff;
  }

  // Return whether this Position is in bounds on a grid with
  // specified width and height.
  bool inBounds(int width, int height) const {
    return x >= 0 && x < width && y >= 0 && y < height;
  }

  // Equality comparison
  bool operator==(const Position &rhs) const {
    return x == rhs.x && y == rhs.y;
  }

  // Inequality comparison
  bool operator!=(const Position &rhs) const {
    return !(*this == rhs);
  }

  // The less-than operator allows Positions to be stored in
  // sets and used as keys in maps.  It compares first by row,
  // then by column.
  bool operator<(const Position &rhs) const {
    if (y < rhs.y) {
      return true;
    } else if (y > rhs.y) {
      return false;
    } else {
      return x < rhs.x;
    }
  }
};

// Stream insertion operator: useful for printing a Position
// for debugging
inline std::ostream &operator<<(std::ostream &out, const Position &pos) {
  out << pos.getX() << "," << pos.getY();
  return out;
}

#endif // POSITION_H
