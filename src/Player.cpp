#include "Player.h"

// Initialize static data
sf::Texture Player::texture;

Player::Player(float x, float y) : moving_entity()
{
    // Load the texture
    texture.loadFromFile("Player.png");
    sprite.setTexture(texture);

    // Set the initial position of the Player
    sprite.setPosition(x, y);

    // Set the velocity of the Player
    velocity = {constants::player_speed, constants::player_speed}; // The Player can only move sideways

    // By default, operations are relative to the sprite's top lh corner
    // Make them relative to the sprite's centre
    sprite.setOrigin(getCentre());
}

// Compute the Player's new position
void Player::update()
{
    // Respond to user input as this will affect how the Player moves
    process_player_input();

    // Move the position of the Player
    sprite.move(velocity);
}

void Player::draw(sf::RenderWindow &window)
{
    // Ask the window to draw the shape for us
    window.draw(sprite);
}

// Respond to input from the player
// If the player presses the left arrow key, move to the left (negative velocity)
// If the player presses the right arrow key, move to the right (positive velocity)
// Otherwise, do not move (zero velocity)
// Do not allow the Player to move off the screen
void Player::process_player_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        // Left arrow key pressed - move to the left
        // Unless the Player has gone past the left hand side
        if (x() >= 0)
            velocity.x = -constants::Player_speed;
        else
            velocity.x = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        // Similarly for the right arrow
        if (x() <= constants::window_width)
            velocity.x = constants::Player_speed;
        else
            velocity.x = 0;
    }
    else
    {
        // Some other key pressed, or no key at all
        velocity.x = 0;
    }
}
