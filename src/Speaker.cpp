#include "Speaker.hpp"

Speaker::Speaker(int z, sf::Sprite sprite, string name) : StaticEntity(z, sprite, name){};

void Speaker::switchState()
{
    isActive = !isActive;
    std::cout << name << " " << (isActive ? "is active" : "is inactive") << '\n';
}

bool Speaker::getState()
{
    return isActive;
}