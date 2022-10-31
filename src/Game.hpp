#pragma once
#include "EntityManager.hpp"
#include <tmxlite/Map.hpp>
#include "Layer.hpp"
class Game
{
public:
    Game();
    void run();

private:
    vector<unique_ptr<MapLayer>> mapLayers;

    sf::RenderWindow window{{constants::window_width, constants::window_height},
                            "Silent Valley Game"};

    sf::View view{sf::Vector2f(constants::window_width / 2, constants::window_height / 2),
                  sf::Vector2f(constants::window_width / 3, constants::window_height / 3)};

    sf::Music music;
};
