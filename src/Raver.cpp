#include "Raver.hpp"

Raver::Raver(float x, float y, int z, sf::Texture &texture, string name) : Human(x, y, z, texture, name)
{
}

Raver::~Raver()
{
}

void Raver::update()
{
    if (checkTarget)
        seek(target);
}

void Raver::setTarget(sf::Vector2f target)
{
    this->target = target;
    checkTarget = true;
}

// void checkObstacles()
// {
//     switch (currentAnimation)
//     {
//     }
// }

void Raver::seek(sf::Vector2f target)
{
    // checkObstacles();
    sf::Time frameTime = frameClock.restart();

    auto diff = target - getPosition();

    if (abs(diff.x) > 16 && abs(diff.y) > 16)
    {
        if (abs(diff.x) > 2 * abs(diff.y))
        {
            velocity.x = (diff.x > 0 ? 1 : -1) * constants::player_speed;
            currentAnimation = diff.x > 0 ? animations["right_walking"] : animations["left_walking"];
            velocity.y = 0;
        }
        else
        {
            velocity.y = (diff.y > 0 ? 1 : -1) * constants::player_speed;
            currentAnimation = diff.y > 0 ? animations["down_walking"] : animations["up_walking"];
            velocity.x = 0;
        }
    }
    else if (abs(diff.x) > 16)
    {
        velocity.x = (diff.x > 0 ? 1 : -1) * constants::player_speed;
        currentAnimation = diff.x > 0 ? animations["right_walking"] : animations["left_walking"];
        velocity.y = 0;
    }
    else if (abs(diff.y) > 16)
    {
        velocity.y = (diff.y > 0 ? 1 : -1) * constants::player_speed;
        currentAnimation = diff.y > 0 ? animations["down_walking"] : animations["up_walking"];
        velocity.x = 0;
    }
    else
    {
        velocity.x = 0;
        velocity.y = 0;
        animatedSprite.stop();
        currentAnimation = animations["up"];
    }
    animatedSprite.play(currentAnimation);
    animatedSprite.move(velocity);

    animatedSprite.update(frameTime);
}