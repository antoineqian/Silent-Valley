#include <SFML/Graphics.hpp>

#include <string>
#include "Map.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>

#include <tmxlite/Map.hpp>
#include "Layer.hpp"
using std::make_shared;
using std::make_unique;
using std::map;
using std::shared_ptr;
using std::string;
using std::vector;
using namespace std::literals;

int main()
{

    tmx::Map gameMap;
    gameMap.load("assets/mainMap.tmx");
    // const auto tilesets = gameMap.getTilesets();
    vector<unique_ptr<MapLayer>> mapLayers;

    // TODO: constants::window_width/window_height are actually hardcoded from this
    // We should add objects like vegetation to prevent the player going anywhere near the limit
    // of the map, and its black zone.
    // auto mapSize = gameMap.getBounds();
    // std::cout << mapSize.height << '\n'
    //           << mapSize.width;

    for (std::size_t i = 0; i < gameMap.getLayers().size(); i++)
    {
        if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Tile)
        {
            mapLayers.push_back(make_unique<MapLayer>(gameMap, i));
        }
    }

    map<int, vector<shared_ptr<Entity>>> gameEntities;

    // shared_ptr<Map> pMap = make_shared<Map>("../assets/layer0.txt", constants::layers.at("ground"));
    // gameEntities[constants::layers.at("ground")].push_back(pMap);

    shared_ptr<Player> pPlayer = make_shared<Player>(constants::window_width / 2, constants::window_height / 2, constants::layers.at("main"));
    gameEntities[constants::layers.at("main")].push_back(pPlayer);

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
        view.setCenter(pPlayer->x(), pPlayer->y());
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
        // pMap->update();
        pPlayer->update();
        for (auto &&layer : mapLayers)
        {
            window.draw(*layer);
        }
        for (const auto &[layer, lEntities] : gameEntities)
        {
            for (auto e : lEntities)
            {
                e->draw(window);
            }
        }
        window.display();
    }
}
