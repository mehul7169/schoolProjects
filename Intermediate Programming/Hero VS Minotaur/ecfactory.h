#ifndef ECFACTORY_H
#define ECFACTORY_H

class EntityController;

class EntityControllerFactory {
private:
  // copy constructor and assignment operator are disallowed
  EntityControllerFactory(const EntityControllerFactory &);
  EntityControllerFactory &operator=(const EntityControllerFactory &);

  // constructor and destructor are private
  EntityControllerFactory();
  ~EntityControllerFactory();

public:
  // Get a pointer to the singleton instance of EntityControllerFactory
  static EntityControllerFactory *getInstance();

  // Create an EntityController, given the character that identifies it.
  // Characters are:
  //   u - UIControl
  //   c - ChaseHero
  //   a - AStarChaseHero
  //   i - Inanimate
  //   m - MysteryController
  EntityController *createFromChar(char c);
};

#endif // ECFACTORY_H
