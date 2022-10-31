#pragma once
#include "Entity.hpp"
class Speaker : public StaticEntity
{
public:
    Speaker(int z, sf::Sprite sprite, string name);
    void switchState();
    bool getState();

private:
    bool isActive{false};
};