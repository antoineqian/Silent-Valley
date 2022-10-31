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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        actionCommand();
    }

    /***
     * MOVEMENT
     */
    bool noKeyWasPressed = true;
    sf::Time frameTime = frameClock.restart();
    auto hitBox = getHitBox();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        noKeyWasPressed = false;
        direction = Direction::left;
        currentAnimation = animations[string(magic_enum::enum_name(direction)) + string("_walking")];

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
        direction = Direction::right;
        currentAnimation = animations[string(magic_enum::enum_name(direction)) + string("_walking")];

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
        direction = Direction::up;
        currentAnimation = animations[string(magic_enum::enum_name(direction)) + string("_walking")];
        if (hitBox.top >= 0)
            velocity.y = -constants::player_speed;
        else
            velocity.y = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        noKeyWasPressed = false;
        direction = Direction::down;
        currentAnimation = animations[string(magic_enum::enum_name(direction)) + string("_walking")];
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

sf::FloatRect Player::getFacePosition()
{
    auto box = getHitBox();
    switch (magic_enum::enum_integer(direction))
    {
    case magic_enum::enum_integer(Direction::up):
        return {box.left, box.top - 8, box.width, 8};
    case magic_enum::enum_integer(Direction::down):
        return {box.left, box.top + box.height, box.width, 8};
    case magic_enum::enum_integer(Direction::left):
        return {box.left - 8, box.top, 8, box.width};
    case magic_enum::enum_integer(Direction::right):
        return {box.left + box.width, box.top, 8, box.width};
    }
}

void Player::actionCommand()
{
    sf::Time elapsed = actionTimer.getElapsedTime();
    if (elapsed.asSeconds() > 1.f)
    {
        EntityManager::inst().playerActionCommand();
        actionTimer.restart();
    }
}