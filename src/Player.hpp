
#pragma once
#include "Entity.hpp"
#include "constants.hpp"
#include "vector"
#include "Human.hpp"
using std::unique_ptr;
using std::vector;

class Player : public Human
{
private:
    void processPlayerInput();

public:
    Player(float x, float y, int z, sf::Texture &texture, string name);
    ~Player();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;
    Player(Player &&) = delete;
    Player &operator=(Player &&) = delete;

    void update() override;
};