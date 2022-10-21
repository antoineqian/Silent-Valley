
#pragma once
#include "Entity.hpp"
#include "constants.hpp"

class Player : public MovingEntity
{
private:
    static sf::Texture texture;

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