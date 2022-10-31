#pragma once
#include "Entity.hpp"
class Speaker : public StaticEntity
{
public:
    Speaker(int z, sf::Sprite sprite, string name);
    void switchState();

private:
    bool isActive{false};
};