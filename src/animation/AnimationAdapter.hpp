#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

class AnimationAdapter
{
private:
    sf::Texture &texture;

public:
    AnimationAdapter(sf::Texture &texture);

    unordered_map<string, Animation> getAnimations();
};