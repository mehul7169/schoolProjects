#include "entity.h"
#include "entitycontroller.h"

Entity::Entity() {
}
Entity::~Entity() {}

  // Entity::Set the glyph that will represent this Entity.
  // Should consist of a single character.
  void Entity::setGlyph(const std::string &glyph) {
  	glyphEntity = glyph;
  }

  // Set the properties of this Entity.  Each character in the
  // string represents a single property.
  void Entity::setProperties(const std::string &props) {
  	property = props;
  }

  // Entity::Get the glyph representing this Entity.
  std::string Entity::getGlyph() const {
  	return glyphEntity;
  }

  // Entity::Get the string containing this Entity's properties.
  std::string Entity::getProperties() const {
  	return property;
  }

  // Return true if the Entity's properties contain the specified
  // character, false otherwise.
  //Todo
  bool Entity::hasProperty(char prop) const {
    return (property.find(prop) != std::string::npos);
  }

  // Entity::Set this Entity's EntityController, which will determine how it moves.
  // The Entity assumes responsibility for deleting it.
  void Entity::setController(EntityController *controller) {
  	Control = controller;
  }

  // Entity::Get this Entity's EntityController.
  EntityController *Entity::getController() {
  	return Control;
  }

  // Entity::Set this Entity's Position.
  void Entity::setPosition(const Position &pos) {
  	positionOfEntity = pos;
  }

  // Return this Entity's Position.
  Position Entity::getPosition() const {
  	return positionOfEntity;
  }
