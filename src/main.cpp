#include <SFML/Graphics.hpp>

#include <string>
#include "Map.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
using std::make_shared;
using std::make_unique;
using std::string;
using std::unordered_map;
using namespace std::literals;

int main()
{
    Map map("../assets/layer0.txt");

    Player player(constants::window_width / 2, constants::window_height / 2);

    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow window{{constants::window_width, constants::window_height},
                            "Silent Valley Game"};

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    window.setFramerateLimit(60); // Max rate is 60 frames per second

    sf::Clock frameClock;
    sf::Texture texture;
    texture.loadFromFile("../assets/complete_player_modernStyle.png");

    AnimationAdapter adapter(texture);
    auto animations = adapter.getAnimations();

    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition({constants::window_width / 2, constants::window_height / 2});

    unique_ptr<Animation> currentAnimation = make_unique<Animation>(animations["down"]);

    // Game loop
    // Clear the screen
    // Check for user input
    // Calculate the updated graphics
    // Display the updated graphics
    while (window.isOpen())
    {
        // Clear the screen
        window.clear(sf::Color::Black);

        // Check for any events since the last loop iteration
        sf::Event event;

        // If the user pressed "Escape", or clicked on "close", we close the window
        // This will terminate the program
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        // Calculate the updated graphics
        map.update();
        player.update();

        map.draw(window);
        // window.draw(animatedSprite);
        player.draw(window);
        window.display();
    }
}
