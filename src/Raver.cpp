#include "Raver.hpp"

Raver::Raver(float x, float y, int z, sf::Texture &texture, string name) : Human(x, y, z, texture, name)
{
}

Raver::~Raver()
{
}

void Raver::update()
{
    // if (checkTarget)
    //     seek(target);
}

// void Raver::setTarget(sf::Vector2f target)
// {
//     this->target = target;
//     checkTarget = true;
// }

// void Raver::seek(sf::Vector2f target)
// {
//     sf::Time frameTime = frameClock.restart();

//     auto diff = target - getPosition();

//     if (abs(diff.x) > 0 && abs(diff.y) > 0)
//     {
//         if (abs(diff.x) > abs(diff.y))
//         {
//             velocity.x = constants::player_speed;
//         }
//         else
//         {
//             velocity.y = constants::player_speed;
//         }
//     }
//     else if (abs(diff.x) > 0)
//     {
//         velocity.x = constants::player_speed;
//     }
//     else if (abs(diff.y) > 0)
//     {
//         velocity.y = constants::player_speed;
//     }
//     animatedSprite.play(currentAnimation);
//     animatedSprite.move(velocity);
//     // if (noKeyWasPressed)
//     // {
//     //     animatedSprite.stop();
//     // }
//     animatedSprite.update(frameTime);
// }