#include "maze.h"
#include "tile.h"
#include "position.h"
#include "tilefactory.h"
#include <iostream>

Maze::Maze(int width, int height) {
  mazeWidth = width;
  mazeHeight = height;

  for (int i = 0; i < width * height; i++) {
    tiles.push_back(nullptr);
  }
}

Maze::~Maze() {
	for (int i = 0; i < (int) tiles.size(); i++) {
		delete tiles[i];
	}
}

int Maze::getWidth() const {
  return mazeWidth;
}

int Maze::getHeight() const {
  return mazeHeight;
}

bool Maze::inBounds(const Position &pos) const {
  return pos.Position::inBounds(mazeWidth, mazeHeight);
}

void Maze::setTile(const Position &pos, Tile *tile) {
  if (Maze::inBounds(pos) == true) {
    int x = pos.getX();
    int y = pos.getY();
    tiles.at(y * mazeWidth + x) = tile;
  }
}

const Tile* Maze::getTile(const Position &pos) const {
  int x = pos.getX();
  int y = pos.getY();
  return tiles.at(y * mazeWidth + x);
}

Maze* Maze::read(std::istream &in) {
	//check in for data
	int width = 0;
	int height = 0;
	int count = 0;

	in >> width >> height;
	if (width == 0 || height == 0) {
		return nullptr;
	}
	Maze * tempMaze = new Maze(width, height);
		
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			char tileCharacter;
			in >> tileCharacter;
     			TileFactory * temporaryFactory = TileFactory::getInstance();
			Tile * temp = temporaryFactory->createFromChar(tileCharacter);
			if (temp == nullptr) {
			  //Add error
			  //exit(1);
			  delete tempMaze;
			  delete temp;
			  return nullptr;
			}
			
			if (j == 0 || j == width) {
				std::string tileChar = temp->getGlyph();
				if (tileChar != "#") {
				  delete tempMaze;
				  delete temp;
				  return nullptr;
				}
			}

	      	Position * pos = new Position(j, i);
			tempMaze->setTile(*pos, temp);

			count++;
	     	delete pos;
		}
	}
	// if ( != height*width) {
	// 	return nullptr;
	// }
	
	return tempMaze;
}




