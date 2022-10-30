#include "Entity.hpp"

// using std::cout;

Entity::Entity(int z, string name) : id(idGenerator++), zIndex(z), name(name)
{
}

sf::FloatRect Entity::getHitBox() const
{
    auto box = getBoundingBox();
    return {box.left + box.width * 0.1f, box.top + box.height * 0.7f, box.width * 0.8f, box.height * 0.3f};
}

// Helper function to get the centre of a sprite
sf::Vector2f Entity::getCentre() const noexcept
{
    auto box = getBoundingBox();
    return {box.width / 2.0f, box.height / 2.0f};
}

// bool operator<(const Entity &e1, const Entity &e2) const
bool Entity::operator<(const Entity &other)
{
    auto box1 = this->getBoundingBox();
    auto box2 = other.getBoundingBox();
    // std::cout << this->name << "is at " << box1.top + box1.height << " while "
    //           << other.name << " is at " << box2.top + box2.height << '\n';
    return (box1.top + box1.height < box2.top + box2.height);
}

// STATIC ENTITY//

StaticEntity::StaticEntity(int z, sf::Sprite sprite, string name) : Entity(z, name), sprite(sprite){};

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

string StaticEntity::getName()
{
    return name;
};

// MOVING ENTITY//

MovingEntity::MovingEntity(int z, string name)
    : Entity(z, name), animatedSprite(sf::seconds(0.2), true, true) {}

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

sf::Vector2f MovingEntity::getVelocity() const
{
    return velocity;
}

void MovingEntity::setPosition(sf::Vector2f position)
{
    animatedSprite.setPosition(position);
}

sf::Vector2f MovingEntity::getPosition() const
{
    return animatedSprite.getPosition();
}