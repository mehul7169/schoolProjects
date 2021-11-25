#ifndef TILEFACTORY_H
#define TILEFACTORY_H

class Tile;

// Singleton factory to create Tile objects.
class TileFactory {
private:
  // copy constructor and assignment operator are disallowed
  TileFactory(const TileFactory &);
  TileFactory &operator=(const TileFactory &);

  // constructor and destructor are private
  TileFactory();
  ~TileFactory();

public:
  // Get a pointer to the singleton TileFactory object
  static TileFactory *getInstance();

  // Create a Tile from its designated character:
  //   # - Wall
  //   . - Floor
  //   < - Goal
  //   m - MysteryTile
  Tile *createFromChar(char c);
};

#endif // TILEFACTORY_H
