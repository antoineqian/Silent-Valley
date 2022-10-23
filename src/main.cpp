#include <SFML/Graphics.hpp>

#include <string>
#include "Map.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
using std::make_shared;
using std::make_unique;
using std::string;
using std::unordered_map;
using std::vector;
using namespace std::literals;

int main()
{
    unordered_map<int, vector<Entity>> gameEntities;
    Map map("assets/layer0.txt", constants::layers.at("ground"));
    gameEntities[constants::layers.at("ground")].push_back(map);
    Player player(constants::window_width / 2, constants::window_height / 2, constants::layers.at("main"));
    gameEntities[constants::layers.at("main")].push_back(player);
    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow window{{constants::window_width, constants::window_height},
                            "Silent Valley Game"};

    sf::View view(sf::Vector2f(constants::window_width / 2, constants::window_height / 2),
                  sf::Vector2f(constants::window_width / 3, constants::window_height / 3));

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    window.setFramerateLimit(60); // Max rate is 60 frames per second

    // Game loop
    // Clear the screen
    // Check for user input
    // Calculate the updated graphics
    // Display the updated graphics
    while (window.isOpen())
    {
        // Clear the screen
        window.clear(sf::Color::Black);
        view.setCenter(player.x(), player.y());
        window.setView(view);

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

        for (const auto &[key, layer] : constants::layers)
        {
            for (auto e : gameEntities[layer])
            {
                e.draw(window);
            }
            // map.draw(window);
            // player.draw(window);
        }
        window.display();
    }
