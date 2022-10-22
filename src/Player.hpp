
#pragma once
#include "Entity.hpp"
#include "constants.hpp"
#include "animation/Animation.hpp"
#include "animation/AnimationAdapter.hpp"
#include "vector"
#include <memory>
using std::unique_ptr;
using std::vector;

class Player : public MovingEntity
{
public:
    unordered_map<string, Animation> animations;
    // unique_ptr<Animation> currentAnimation;
    Animation currentAnimation;

private:
    static sf::Texture texture;

    sf::Clock frameClock;

    void processPlayerInput();

public:
    Player(float x, float y);
    ~Player();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;
    Player(Player &&) = delete;
    Player &operator=(Player &&) = delete;

    void draw(sf::RenderWindow &window) const override;
    void update() override;
};