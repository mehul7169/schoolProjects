#include <sstream>
#include <iostream>
#include "tctestpp.h"
#include "position.h"
#include "tile.h"
#include "tilefactory.h"
#include "textui.h"
#include "maze.h"
#include "tilefactory.h"

using std::cout; using std::endl;

Maze *readFromString(const std::string &s) {
  std::stringstream ss(s);
  return Maze::read(ss);
}
//good maze data
const char *m1 =
  "10 6\n"
  "##########\n"
  "#........#\n"
  "#.###....#\n"
  "#.#......#\n"
  "#.....<..#\n"
  "##########\n";

//bad maze data
const char *m2 =
  "9 6\n"
  "##########\n"
  "#........#\n"
  "#.###....#\n"
  "#.#......#\n"
  "#.....<..#\n"
  "##########\n";

//bad maze data
const char *m3 =
  "10 6\n"
  "##########\n"
  "#........#\n"
  "#.*##....#\n"
  "#.#......#\n"
  "#.....<..#\n"
  "##########\n";

const char *m2_invalid_dims =
    "6\n"
    "##########\n"
    "#........#\n"
    "#.###....#\n"
    "#.#......#\n"
    "#.....<..#\n"
    "##########\n";

const char *m3_illegal_row =
    "10 6\n"
    "##########\n"
    "#........#\n"
    "#.###....#\n"
    "#.#......\n"
    "#.....<..#\n"
    "##########\n";

struct TestObjs {
  Maze *maze1;
  Maze *maze2;
  Maze *maze3;
  Maze *maze4;
  Maze *maze5;
};

TestObjs *setup() {
  TestObjs *objs = new TestObjs;
  objs->maze1 = readFromString(m1);
  objs->maze2 = readFromString(m2);
  objs->maze3 = readFromString(m3);
  objs->maze4 = readFromString(m2_invalid_dims);
  objs->maze5 = readFromString(m3_illegal_row);  
  return objs;
}

void cleanup(TestObjs *objs) {
  delete objs->maze1;
  delete objs->maze2;
  delete objs->maze3;
  delete objs->maze4;
  delete objs->maze5;
  delete objs;
}

void testGetWidth(TestObjs *objs);
void testGetHeight(TestObjs *objs);
void testGetTile(TestObjs *objs);
void testInBounds(TestObjs *objs);
void testSetTile(TestObjs *objs);
void testReadMaze(TestObjs *objs);
void testInvalidMazeDimensions(TestObjs *objs);

int main(int argc, char *argv[]) {
  TEST_INIT();

  // allow test name to be specified on the command line
  if (argc > 1) {
    tctest_testname_to_execute = argv[1];
  }

  TEST(testGetWidth);
  TEST(testGetHeight);
  TEST(testGetTile);
  TEST(testInBounds);
  TEST(testSetTile);
  TEST(testReadMaze);
  TEST(testInvalidMazeDimensions);

  TEST_FINI();
}

void testInBounds(TestObjs *objs){
  Position p1(11, 5);
  Position p2(11, 7);
  Position p3(6, 11);
  Position p4(4, 3);
  Position p5(0, -1);
  ASSERT(!objs->maze1->inBounds(p1));
  ASSERT(!objs->maze1->inBounds(p2));
  ASSERT(!objs->maze1->inBounds(p3));
  ASSERT(objs->maze1->inBounds(p4));
  ASSERT(!objs->maze1->inBounds(p5));
}

void testGetWidth(TestObjs *objs) {
  ASSERT(10 == objs->maze1->getWidth());
}

void testGetHeight(TestObjs *objs) {
  ASSERT(6 == objs->maze1->getHeight());
}

void testGetTile(TestObjs *objs) {
  const Tile *p1 = objs->maze1->getTile(Position(0, 0));
  ASSERT(p1->getGlyph() == "#");
  ASSERT(!p1->isGoal());

  const Tile *p2 = objs->maze1->getTile(Position(1, 1));
  ASSERT(p2->getGlyph() == ".");
  ASSERT(!p2->isGoal());

  const Tile *p3 = objs->maze1->getTile(Position(7, 4));
  ASSERT(!p3->isGoal());
}

void testSetTile(TestObjs *) {
  Maze *maze = new Maze(10, 5);

  Tile *tile1 = TileFactory::getInstance()->createFromChar('#');
  Tile *tile2 = TileFactory::getInstance()->createFromChar('.');
  maze->setTile(Position(0, 0), tile1);
  ASSERT("#" == maze->getTile(Position(0, 0))->getGlyph());
  maze->setTile(Position(4, 3), tile2);
  ASSERT("." == maze->getTile(Position(4, 3))->getGlyph());

  TileFactory *tfac = TileFactory::getInstance();
  Tile *tile = tfac->createFromChar('.');
  Position p1(6, 3);
  maze->setTile(p1, tile);
  const Tile *t1 = maze->getTile(p1);
  ASSERT(t1->getGlyph() == ".");

  delete maze;
}

void testReadMaze(TestObjs *objs){
  ASSERT(!(objs->maze1 == nullptr));
  ASSERT(objs->maze2 == nullptr);
  ASSERT(objs->maze3 == nullptr);
}

void testInvalidMazeDimensions(TestObjs *objs) {
  ASSERT(objs->maze4 == nullptr);
  ASSERT(objs->maze5 == nullptr);
}
