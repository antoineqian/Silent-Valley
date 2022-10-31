#include "Player.hpp"
#include <cmath>
using std::abs;
#include <iostream>
using std::cout;
using std::make_shared;

Player::Player(float x, float y, int z, sf::Texture &texture, string name) : Human(x, y, z, texture, name)
{
}

Player::~Player()
{
}

// Compute the Player's new position
void Player::update()
{ // Respond to user input as this will affect how the Player moves
    processPlayerInput();
}

// Respond to input from the player
// If the player presses the left arrow key, move to the left (negative velocity)
// If the player presses the right arrow key, move to the right (positive velocity)
// If the player presses the down arrow key, move down (negative velocity)
// If the player presses the up arrow key, move up (positive velocity)
// Otherwise, do not move (zero velocity)
// Do not allow the Player to move off the screen
// Play animation according to direction of movement
void Player::processPlayerInput()
{
    bool noKeyWasPressed = true;
    sf::Time frameTime = frameClock.restart();
    auto hitBox = getHitBox();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        noKeyWasPressed = false;
        status = "walking_left";
        currentAnimation = animations[status];

        // Left arrow key pressed - move to the left
        // Unless the Player has gone past the left hand side
        if (hitBox.left >= 0)
            velocity.x = -constants::player_speed;
        else
            velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        noKeyWasPressed = false;
        status = "walking_right";
        currentAnimation = animations[status];

        // Similarly for the right arrow
        if (hitBox.left + hitBox.width <= constants::window_width)
            velocity.x = constants::player_speed;
        else
            velocity.x = 0;
    }
    else
    {
        velocity.x = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        noKeyWasPressed = false;
        status = "walking_up";
        currentAnimation = animations[status];
        if (hitBox.top >= 0)
            velocity.y = -constants::player_speed;
        else
            velocity.y = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        noKeyWasPressed = false;
        status = "walking_down";
        currentAnimation = animations[status];
        if (hitBox.top + hitBox.height <= constants::window_height)
            velocity.y = constants::player_speed;
        else
            velocity.y = 0;
    }
    else
    {
        velocity.y = 0;
    }
    animatedSprite.play(currentAnimation);
    animatedSprite.move(velocity);
    if (noKeyWasPressed)
    {
        animatedSprite.stop();
    }
    animatedSprite.update(frameTime);
}
