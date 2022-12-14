
#pragma once
#include "Entity.hpp"
#include "animation/Animation.hpp"
#include "animation/AnimationAdapter.hpp"
#include <magic_enum.hpp>

enum class Direction
{
    up,
    down,
    left,
    right
};
class Human : public MovingEntity
{
public:
    Human(float x, float y, int z, sf::Texture &texture, string name);
    ~Human();
    sf::FloatRect getHitBox() const override;
    sf::FloatRect getBoundingBox() const override;
};