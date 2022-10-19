#include "Map.hpp"
#include "WalkTile.hpp"
#include "BlockTile.hpp"
#include <stdexcept>
#include "TileDrawer.hpp"

using std::make_shared;
using std::make_unique;
using std::move;

Map::Map(vector<vector<char>> mapDescription, shared_ptr<TileDrawer> pDrawer) : pDrawer(pDrawer)
{
	for (int i = 0; i < mapDescription.size(); ++i)
	{
		auto row = mapDescription[i];

		vector<unique_ptr<Tile>> tileRow;

		for (auto j = 0; j < row.size(); ++j)
		{
			auto ch = row[j];
			if (ch == 'w')
			{
				tileRow.push_back(make_unique<WalkTile>(sf::Vector2f(j * 16, i * 16), pDrawer));
			}
			else if (ch == 'b')
			{
				tileRow.push_back(make_unique<BlockTile>(sf::Vector2f(j * 16, i * 16), pDrawer));
			}
			else
			{
				throw std::invalid_argument("Unknown tile type.");
			}
		}
		tiles.push_back(std::move(tileRow));
	}
}

void Map::draw(sf::RenderWindow &window) const
{

	for (auto &&row : tiles)
	{

		for (auto &&tile : row)
		{
			tile->draw(window);
		}
	}
}

void Map::update()
{
}