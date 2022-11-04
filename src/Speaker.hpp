#pragma once
#include "Entity.hpp"
#include "gui/Observable.hpp"
class Speaker : public StaticEntity, public Observable<Speaker>
{
public:
    Speaker(int z, sf::Sprite sprite, string name);
    void switchState();
    bool getState();

private:
    bool isActive{false};
};