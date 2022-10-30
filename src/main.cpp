#include <SFML/Graphics.hpp>

#include <string>
#include "Player.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>

#include <tmxlite/Map.hpp>
#include "Layer.hpp"

#include "EntityManager.hpp"
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
    const auto &tileSets = gameMap.getTilesets();
    for (auto &ts : tileSets)
    {
        std::string s("Objects");
        if (ts.getName() == s)
        {
            EntityManager::inst().setObjectTileset(ts);
        }
    }

    vector<unique_ptr<MapLayer>> mapLayers;

    for (std::size_t i = 0; i < gameMap.getLayers().size(); i++)
    {
        if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Tile)
        {
            mapLayers.push_back(make_unique<MapLayer>(gameMap, i));
        }
        if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Object)
        {
            const auto &objectLayer = gameMap.getLayers()[i]->getLayerAs<tmx::ObjectGroup>();
            for (const auto &object : objectLayer.getObjects())
            {
                EntityManager::inst().addObjectAsEntity(object);
            }
        }
    }

    EntityManager::inst().addPlayer("assets/complete_player_modernStyle.png");

    // Add some NPCs
    EntityManager::inst().addRaver(constants::window_width / 3, constants::window_height / 3, "assets/Premade_Character_07.png");
    EntityManager::inst().addRaver(constants::window_width / 3, 2 * constants::window_height / 3, "assets/Premade_Character_07.png");

    // Create the game's window using an object of class RenderWindow
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
        view.setCenter(EntityManager::inst().getPlayer().x(), EntityManager::inst().getPlayer().y());
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
        EntityManager::inst().getPlayer().update();
        EntityManager::inst().handleCollisions();

        for (auto &&layer : mapLayers)
        {
            window.draw(*layer);
        }
        EntityManager::inst().draw(window);
        window.display();
    }
}
