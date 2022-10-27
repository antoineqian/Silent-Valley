#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "animation/AnimatedSprite.hpp"

#include <string>
#include <iostream>

using std::string;
// Abstract base class to represent any graphical entity on the screen
class Entity : public sf::Drawable
{
protected:
  int zIndex;

public:
  string name;

  Entity(int z, string name);

  // The update member function will compute the new position, appearance, etc of the object
  // The draw member function will cause the updated object to be displayed in the game window
  virtual void update() = 0;

  // Helper function to get the bounding box of a sprite
  virtual sf::FloatRect getBoundingBox() const = 0;
  // Helper function to get the hitbox of an entity to handle collisions
  virtual sf::FloatRect getHitBox() const;
  // Helper function to get the centre of a sprite
  sf::Vector2f getCentre() const noexcept;

  // Helper functions to get the position of the sprite
  virtual float x() const noexcept = 0;
  virtual float y() const noexcept = 0;

  // Virtual destructor
  virtual ~Entity() {}

  bool operator<(const Entity &other);
};

class StaticEntity : public Entity
{
protected:
  sf::Sprite sprite;

public:
  StaticEntity(int z, sf::Sprite sprite, string name);
  float x() const noexcept override;
  float y() const noexcept override;
  sf::FloatRect getBoundingBox() const override;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void update() override;
  string getName();
  virtual ~StaticEntity() {}
};

// Abstract base class to represent graphical entities which can move around the screen
class MovingEntity : public Entity
{
public:
  MovingEntity(int z, string name);

  float x() const noexcept override;
  float y() const noexcept override;
  sf::FloatRect getBoundingBox() const override;
  virtual ~MovingEntity() {}

protected:
  AnimatedSprite animatedSprite;

  // SFML vector to store the object's velocity
  sf::Vector2f velocity;
};

#endif // ENTITY_H
