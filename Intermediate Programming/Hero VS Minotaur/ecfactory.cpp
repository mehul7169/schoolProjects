#include <stdexcept>
#include "uicontrol.h"
#include "chasehero.h"
#include "astarchasehero.h"
#include "inanimate.h"
#include "mysterycontroller.h"
#include "ecfactory.h"

EntityControllerFactory::EntityControllerFactory() {
}

EntityControllerFactory::~EntityControllerFactory() {
}

EntityControllerFactory *EntityControllerFactory::getInstance() {
  static EntityControllerFactory theInstance;
  return &theInstance;
}

EntityController *EntityControllerFactory::createFromChar(char c) {
  switch (c) {
  case 'u':
    return new UIControl();
  case 'c':
    return new ChaseHero();
  case 'a':
    return new AStarChaseHero();
  case 'i':
    return new Inanimate();
  case 'm':
    return new MysteryController();
  }
  throw std::runtime_error("Unknown character");
}
