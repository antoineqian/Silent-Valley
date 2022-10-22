
#include "AnimationAdapter.hpp"

AnimationAdapter::AnimationAdapter(sf::Texture &texture) : texture(texture)
{
}

unordered_map<string, Animation> AnimationAdapter::getAnimations()
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

    animations.insert({"down", walkingAnimationDown});

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(192, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 16, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 32, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 48, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 64, 64, 16, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192 + 80, 64, 16, 32));
    animations.insert({"left", walkingAnimationLeft});

    Animation walkingAnimationRight;
    walkingAnimationRight.addFrame(sf::IntRect(0, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 16, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 32, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 48, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 64, 64, 16, 32));
    walkingAnimationRight.addFrame(sf::IntRect(0 + 80, 64, 16, 32));
    animations.insert({"right", walkingAnimationRight});

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(96, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 16, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 32, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 48, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 64, 64, 16, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96 + 80, 64, 16, 32));
    animations.insert({"up", walkingAnimationUp});

    return animations;
}
// sf::Clock frameClock;

// float speed = 80.f;
// bool noKeyWasPressed = true;

// while (window.isOpen())
// {
//     sf::Event event;
//     while (window.pollEvent(event))
//     {
//         if (event.type == sf::Event::Closed)
//             window.close();
//         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//             window.close();
//     }

//     sf::Time frameTime = frameClock.restart();

//     // if a key was pressed set the correct animation and move correctly
//     sf::Vector2f movement(0.f, 0.f);
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//     {
//         currentAnimation = &walkingAnimationUp;
//         movement.y -= speed;
//         noKeyWasPressed = false;
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//     {
//         currentAnimation = &walkingAnimationDown;
//         movement.y += speed;
//         noKeyWasPressed = false;
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//     {
//         currentAnimation = &walkingAnimationLeft;
//         movement.x -= speed;
//         noKeyWasPressed = false;
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//     {
//         currentAnimation = &walkingAnimationRight;
//         movement.x += speed;
//         noKeyWasPressed = false;
//     }
//     animatedSprite.play(*currentAnimation);
//     animatedSprite.move(movement * frameTime.asSeconds());

//     // if no key was pressed stop the animation
//     if (noKeyWasPressed)
//     {
//         animatedSprite.stop();
//     }
//     noKeyWasPressed = true;

//     // update AnimatedSprite
//     animatedSprite.update(frameTime);

//     // draw
//     window.clear();
//     window.draw(animatedSprite);
//     window.display();
// }

// return 0;
// }