
#pragma once
#include "Entity.hpp"

class Player : public MovingEntity
{
public:
    Player(sf::Vector2f position);
    ~Player();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;
    Player(Player &&) = delete;
    Player &operator=(Player &&) = delete;

    void draw(sf::RenderWindow &window) const override;
    void update() override;
};