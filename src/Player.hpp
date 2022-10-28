
#pragma once
#include "Entity.hpp"
#include "constants.hpp"
#include "animation/Animation.hpp"
#include "animation/AnimationAdapter.hpp"
#include "vector"
using std::unique_ptr;
using std::vector;

class Player : public MovingEntity
{
private:
    unordered_map<string, Animation> animations;
    Animation currentAnimation;
    static sf::Texture texture;

    sf::Clock frameClock;

    void processPlayerInput();

public:
    Player(float x, float y, int z, string name);
    ~Player();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;
    Player(Player &&) = delete;
    Player &operator=(Player &&) = delete;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update() override;
    sf::FloatRect getHitBox() const override;
    sf::FloatRect getBoundingBox() const override;
};