#include "Player.hpp"
#include <cmath>
using std::abs;
#include <iostream>

// Initialize static data
sf::Texture Player::texture;

Player::Player(float x, float y) : MovingEntity()
{
    // Load the texture
    texture.loadFromFile("../assets/complete_player_modernStyle.png");
    AnimationAdapter adapter(texture);
    animations = adapter.getAnimations();

    // Set the initial position of the Player
    animatedSprite.setPosition(x, y);
    currentAnimation = animations["down"];

    // Set the velocity of the Player
    velocity = {constants::player_speed, constants::player_speed}; // The Player can only move sideways

    // By default, operations are relative to the sprite's top lh corner
    // Make them relative to the sprite's centre
    animatedSprite.setOrigin(getCentre());
}

Player::~Player()
{
}

// Compute the Player's new position
void Player::update()
{
    // Respond to user input as this will affect how the Player moves
    processPlayerInput();
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(animatedSprite);
}

// Respond to input from the player
// If the player presses the left arrow key, move to the left (negative velocity)
// If the player presses the right arrow key, move to the right (positive velocity)
// If the player presses the down arrow key, move down (negative velocity)
// If the player presses the up arrow key, move up (positive velocity)
// Otherwise, do not move (zero velocity)
// Do not allow the Player to move off the
// Play animation according to direction of movement
void Player::processPlayerInput()
{
    bool noKeyWasPressed = true;
    sf::Time frameTime = frameClock.restart();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        noKeyWasPressed = false;
        currentAnimation = animations["left"];

        // Left arrow key pressed - move to the left
        // Unless the Player has gone past the left hand side
        if (x() >= 0)
            velocity.x = -constants::player_speed;
        else
            velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        noKeyWasPressed = false;
        currentAnimation = animations["right"];

        // Similarly for the right arrow
        if (x() <= constants::window_width)
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
        currentAnimation = animations["up"];

        if (y() >= 0)
            velocity.y = -constants::player_speed;
        else
            velocity.y = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        noKeyWasPressed = false;
        currentAnimation = animations["down"];

        if (y() <= constants::window_height)
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
