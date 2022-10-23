#include "Map.hpp"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

void initMap(Map &map)
{
    for (auto row : map.description)
    {
        for (auto c : row)
        {
            if (!constants::tilePositionsInMap.contains(c))
            {
                throw std::invalid_argument("Unknown tile type.");
            }
        }
    }
    map.groundTexture.loadFromFile("../assets/tiles.png");
    for (const auto &[tileType, pos] : constants::tilePositionsInMap)
    {
        sf::IntRect subRect;
        subRect.left = pos.x * constants::tile_size;
        subRect.top = pos.y * constants::tile_size;
        subRect.width = constants::tile_size;
        subRect.height = constants::tile_size;
        sf::Sprite sprite(map.groundTexture, subRect);
        map.sprites[tileType] = sprite;
    }
}

Map::Map(string descriptionFilePath)
{
    std::ifstream file(descriptionFilePath);
    string line;

    while (std::getline(file, line))
    {
        vector<char> row;
        std::istringstream iss(line);
        char c;
        while (iss >> c)
        {
            row.push_back(c);
        }
        description.push_back(row);
    }
    initMap(*this);
}

Map::Map(vector<vector<char>> mapDescription) : description(mapDescription)
{
    initMap(*this);
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
            spriteToDraw.setPosition(j * constants::tile_size, i * constants::tile_size);
            window.draw(spriteToDraw);
        }
    }
}

void Map::update()
{
}