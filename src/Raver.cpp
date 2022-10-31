#include "Raver.hpp"

Raver::Raver(float x, float y, int z, sf::Texture &texture, string name) : Human(x, y, z, texture, name)
{
}
std::unique_ptr<Raver> Raver::create(float x, float y, int z, sf::Texture &texture, string name)
{
    return std::unique_ptr<Raver>(new Raver(x, y, z, texture, name));
}

std::shared_ptr<Raver> Raver::getptr()
{
    return shared_from_this();
}

Raver::~Raver()
{
}

void Raver::update()
{

    if (pCurrentState)
        pCurrentState->execute(shared_from_this());
    sf::Time frameTime = frameClock.restart();
    animatedSprite.play(currentAnimation);
    animatedSprite.move(velocity);
    animatedSprite.update(frameTime);
}

bool Raver::targetReached()
{
    auto diff = target - getPosition();
    return (abs(diff.x) < 16 && abs(diff.y) < 16);
}

void Raver::setAnimation(string animationName)
{
    currentAnimation = animations[animationName];
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

void Raver::seekTarget()
{
    if (targetReached())
    {
        velocity.x = 0;
        velocity.y = 0;
        animatedSprite.stop();
        currentAnimation = animations["up_walking"];
        return;
    }
    // checkObstacles();

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
}

void Raver::changeState(shared_ptr<State> pNewState)
{
    // make sure both states are both valid before attempting to
    // call their methods
    // assert(pCurrentState && pNewState);

    // call the exit method of the existing state
    // pCurrentState->exit(shared_from_this());

    // change state to the new state
    pCurrentState = pNewState;
    auto ptr = getptr();

    // call the entry method of the new state
    pCurrentState->enter(ptr);
}
