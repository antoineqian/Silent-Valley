#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "animation/AnimatedSprite.hpp"

// Abstract base class to represent any graphical entity on the screen
class Entity : public sf::Drawable
{
protected:
  int zIndex;

public:
  Entity(int z);

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
};

class StaticEntity : public Entity
{
protected:
  sf::Sprite sprite;

public:
  StaticEntity(int z, sf::Sprite sprite);
  float x() const noexcept override;
  float y() const noexcept override;
  sf::FloatRect getBoundingBox() const override;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void update() override;

  virtual ~StaticEntity() {}
};

// Abstract base class to represent graphical entities which can move around the screen
class MovingEntity : public Entity
{
public:
  MovingEntity(int z);

  float x() const noexcept override;
  float y() const noexcept override;
  sf::FloatRect getBoundingBox() const override;
  virtual ~MovingEntity() {}

protected:
  AnimatedSprite animatedSprite;

  sf::Vector2f velocity;

  // SFML vector to store the object's velocity
  // This is the distance the ball moves between screen updates
};

#endif // ENTITY_H
