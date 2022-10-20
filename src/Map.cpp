#include "Map.hpp"
#include <stdexcept>

using std::make_shared;
using std::make_unique;
using std::move;

Map::Map(vector<vector<char>> mapDescription) : description(mapDescription)
{
    groundTexture.loadFromFile("../assets/tiles.png");
    for (const auto &[tileType, pos] : constants::tilePositionsInMap)
    {
        sf::IntRect subRect;
        subRect.left = pos.x * constants::tile_size;
        subRect.top = pos.y * constants::tile_size;
        subRect.width = constants::tile_size;
        subRect.height = constants::tile_size;
        sf::Sprite sprite(groundTexture, subRect);
        sprites[tileType] = sprite;
    }
}

void Map::draw(sf::RenderWindow &window) const
{

    for (int i = 0; i < description.size(); ++i)
    {
        auto row = description[i];

        for (int j = 0; j < row.size(); ++j)
        {
            char tileType = row[j];
            auto spriteToDraw = sprites.at(tileType);
            spriteToDraw.setPosition(i * constants::tile_size, j * constants::tile_size);
            window.draw(spriteToDraw);
        }
    }
}

void Map::update()
{
}