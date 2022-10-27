#include "Entity.hpp"
#include <iostream>
// using std::cout;

Entity::Entity(int z) : zIndex(z)
{
}

sf::FloatRect Entity::getHitBox() const
{
    return getBoundingBox();
}

// Helper function to get the centre of a sprite
sf::Vector2f Entity::getCentre() const noexcept
{
    auto box = getBoundingBox();
    return {box.width / 2.0f, box.height / 2.0f};
}

// STATIC ENTITY//

StaticEntity::StaticEntity(int z, sf::Sprite sprite) : Entity(z), sprite(sprite){};

void StaticEntity::update()
{
    // Do nothing since the entity is static
}

void StaticEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

// Helper function to get the bounding box of a sprite
sf::FloatRect StaticEntity::getBoundingBox() const
{
    return sprite.getGlobalBounds();
}

// Helper functions to get the position of the sprite
float StaticEntity::x() const noexcept
{
    return sprite.getPosition().x;
}
float StaticEntity::y() const noexcept
{
    return sprite.getPosition().y;
}

// MOVING ENTITY//

MovingEntity::MovingEntity(int z) : Entity(z), animatedSprite(sf::seconds(0.2), true, true) {}

sf::FloatRect MovingEntity::getBoundingBox() const
{
    return animatedSprite.getGlobalBounds();
}

// Helper functions to get the position of the sprite
float MovingEntity::x() const noexcept
{
    // TODO: Use bounding box here to handle "collision with the screen"
    // std::cout << "x :" << animatedSprite.getPosition().x << " \n ";
    return animatedSprite.getPosition().x;
}
float MovingEntity::y() const noexcept
{
    // std::cout << "y :" << animatedSprite.getPosition().y << " \n ";
    return animatedSprite.getPosition().y;
}