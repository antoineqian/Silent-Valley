
#include "AnimationAdapter.hpp"

// AnimationAdapter::AnimationAdapter(sf::Texture &texture) : texture(texture)
// {
// }

unordered_map<string, Animation> AnimationAdapter::getAnimations(sf::Texture &texture)
{
    unordered_map<string, Animation> animations;
    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(288, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 16, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 32, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 48, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 64, 64, 16, 32));
    walkingAnimationDown.addFrame(sf::IntRect(288 + 80, 64, 16, 32));

    animations.insert({"down_walking", walkingAnimationDown});

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(192, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 16, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 32, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 48, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 64, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 80, 64, 16, 32));
    animations.insert({"left_walking", walkingAnimationLeft});

    Animation walkingAnimationRight;
    walkingAnimationRight.addFrame(sf::IntRect(0, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 16, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 32, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 48, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 64, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 80, 64, 16, 32));
    animations.insert({"right_walking", walkingAnimationRight});

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(96, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 16, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 32, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 48, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 64, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 80, 64, 16, 32));
    animations.insert({"up_walking", walkingAnimationUp});

    return animations;
}
