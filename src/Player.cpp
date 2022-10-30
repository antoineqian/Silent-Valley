#include "Player.hpp"
#include <cmath>
using std::abs;
#include <iostream>
using std::cout;
using std::make_shared;

Player::Player(float x, float y, int z, sf::Texture &texture, string name) : MovingEntity(z, name)
{
    // texture.loadFromFile("assets/complete_player_modernStyle.png");
    animations = AnimationAdapter::getAnimations(texture);
    // animations = adapter.getAnimations();

    // Set the initial position of the Player
    animatedSprite.setPosition(x, y);
    currentAnimation = animations["down"];
    animatedSprite.setAnimation(currentAnimation);

    // currentAnimation = this->animations["down"];
    // animatedSprite.setAnimation(currentAnimation);

    // Set the velocity of the Player
    velocity = {constants::player_speed, constants::player_speed};
}

Player::~Player()
{
}

// Compute the Player's new position
void Player::update()
{ // Respond to user input as this will affect how the Player moves
    processPlayerInput();
}
void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(animatedSprite, states);
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
        currentAnimation = animations["left"];

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
        currentAnimation = animations["right"];

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
        currentAnimation = animations["up"];
        if (hitBox.top >= 0)
            velocity.y = -constants::player_speed;
        else
            velocity.y = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        noKeyWasPressed = false;
        currentAnimation = animations["down"];
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

sf::FloatRect Player::getBoundingBox() const
{
    auto box = animatedSprite.getGlobalBounds();
    // std::cout << "Left :" << box.left << " / Top : " << box.top + 12 << '\n';
    return {box.left, box.top + 12, constants::tile_size, constants::player_height};
}

sf::FloatRect Player::getHitBox() const
{
    auto box = getBoundingBox();
    // std::cout << "Left :" << box.left << " / Top : " << box.top + 12 << '\n';
    return {box.left + box.width * 0.1f, box.top + box.height * 0.7f, box.width * 0.8f, box.height * 0.3f};
    // return box;
}
