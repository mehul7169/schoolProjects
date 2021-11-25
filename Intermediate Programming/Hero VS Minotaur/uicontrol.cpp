#include "uicontrol.h"
#include "game.h"
#include "ui.h"
#include "entity.h"

UIControl::UIControl() {}

UIControl::~UIControl() {}

Direction UIControl::getMoveDirection(Game *game, Entity *) {
  UI *gameUI = game->getUI();
  gameUI = UI::getInstance();

  //EntityController UIController = entity->getController();
  Direction proposedMove = gameUI->getMoveDirection();
  return proposedMove;
}

bool UIControl::isUser() const {
  return true;
}

