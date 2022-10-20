#include "Map.hpp"
#include "WalkTile.hpp"
#include "BlockTile.hpp"
#include <stdexcept>

using std::make_shared;
using std::make_unique;
using std::move;

Map::Map(vector<vector<char>> mapDescription) : description(mapDescription)
{
}

// void Map::draw(sf::RenderWindow &window) const
// {

// 	// for (auto &&row : description)
// 	// {

// 	// 	for (auto &&tile : row)
// 	// 	{
// 	// 		tileset->draw(tile, position);
// 	// 	}
// 	// }
// }

// void Map::update()
// {
// }