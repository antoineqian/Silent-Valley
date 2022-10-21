#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

// Abstract base class to represent any graphical entity on the screen
class Entity
{
protected:
  sf::Sprite sprite;

public:
  // The update member function will compute the new position, appearance, etc of the object
  // The draw member function will cause the updated object to be displayed in the game window
  virtual void update() = 0;
  virtual void draw(sf::RenderWindow &window) const = 0;

  // Helper function to get the bounding box of a sprite
  sf::FloatRect getBoundingBox() const noexcept;

  // Helper function to get the centre of a sprite
  sf::Vector2f getCentre() const noexcept;

  // Helper functions to get the position of the sprite
  float x() const noexcept;
  float y() const noexcept;

  // Virtual destructor
  virtual ~Entity() {}
};

// Abstract base class to represent graphical entities which can move around the screen
class MovingEntity : public Entity
{
protected:
  // SFML vector to store the object's velocity
  // This is the distance the ball moves between screen updates
  sf::Vector2f velocity;
};

#endif // ENTITY_H
