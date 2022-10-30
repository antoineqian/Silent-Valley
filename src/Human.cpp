#include "Human.hpp"

Human::Human(float x, float y, int z, sf::Texture &texture, string name) : MovingEntity(z, name)
{
    animations = AnimationAdapter::getAnimations(texture);

    // Set the initial position
    animatedSprite.setPosition(x, y);
    currentAnimation = animations["down"];
    animatedSprite.setAnimation(currentAnimation);

    velocity = {constants::player_speed, constants::player_speed};
}

Human::~Human()
{
}

sf::FloatRect Human::getBoundingBox() const
{
    auto box = animatedSprite.getGlobalBounds();
    // std::cout << "Left :" << box.left << " / Top : " << box.top + 12 << '\n';
    return {box.left, box.top + 12, constants::tile_size, constants::player_height};
}

sf::FloatRect Human::getHitBox() const
{
    auto box = getBoundingBox();
    // std::cout << "Left :" << box.left << " / Top : " << box.top + 12 << '\n';
    return {box.left + box.width * 0.1f, box.top + box.height * 0.7f, box.width * 0.8f, box.height * 0.3f};
    // return box;
}
