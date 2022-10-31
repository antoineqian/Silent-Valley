
#pragma once
#include "Entity.hpp"
#include "constants.hpp"
#include "vector"
#include "Human.hpp"
#include "EntityManager.hpp"
using std::unique_ptr;
using std::vector;

class Player : public Human
{
private:
    void processPlayerInput();
    void actionCommand();
    sf::Clock actionTimer;

public:
    Player(float x, float y, int z, sf::Texture &texture, string name);
    ~Player();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;
    Player(Player &&) = delete;
    Player &operator=(Player &&) = delete;

    void update() override;
    sf::FloatRect getFacePosition();
};