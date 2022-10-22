#include "Entity.hpp"
// Helper function to get the bounding box of a sprite
sf::FloatRect Entity::getBoundingBox() const noexcept
{
    return sprite.getGlobalBounds();
}

// Helper function to get the centre of a sprite
sf::Vector2f Entity::getCentre() const noexcept
{
    auto box = getBoundingBox();
    return {box.width / 2.0f, box.height / 2.0f};
}

// Helper functions to get the position of the sprite
float Entity::x() const noexcept
{
    return sprite.getPosition().x;
}
float Entity::y() const noexcept
{
    return sprite.getPosition().y;
}

MovingEntity::MovingEntity() : animatedSprite(sf::seconds(0.2), true, true) {}

// Helper functions to get the position of the sprite
float MovingEntity::x() const noexcept
{
    return animatedSprite.getPosition().x;
}
float MovingEntity::y() const noexcept
{
    return animatedSprite.getPosition().y;
}