#pragma once
#include "Human.hpp"
#include "state/State.hpp"
#include "state/RaverStates.hpp"
#include <memory>
using std::make_unique;
using std::unique_ptr;
class State;
/**
 * @brief Generic non player character class
 *
 */
class Raver : public Human, public std::enable_shared_from_this<Raver>
{
public:
    Raver(float x, float y, int z, sf::Texture &texture, string name);
    ~Raver();
    void update() override;
    void setTarget(sf::Vector2f target);
    bool targetReached();
    void setAnimation(string animationName);
    void changeState(std::unique_ptr<State> state);
    std::unique_ptr<State> currentState;
    void seekTarget();
    static std::unique_ptr<Raver> create(float x, float y, int z, sf::Texture &texture, string name);
    std::shared_ptr<Raver> getptr();

private:
    bool checkTarget = false;
    sf::Vector2f target;
};