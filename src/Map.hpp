#pragma once
#include <vector>
#include <memory>
#include "Entity.hpp"
// #include "Tileset.hpp"
// #include "Tile.hpp"
using std::unique_ptr;
using std::vector;

class Map : public Entity
{
public:
	Map(vector<vector<char>> mapDescription);

	// void draw(sf::RenderWindow &window) const override;
	// void update() override;

	vector<vector<char>> description;
	// Tileset tileset;

	// vector<vector<unique_ptr<Tile>>> tiles;
	// shared_ptr<TileDrawer> pDrawer;
};