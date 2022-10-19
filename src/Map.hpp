#pragma once
#include <vector>
#include <memory>

#include "Tile.hpp"
using std::unique_ptr;
using std::vector;

class Map : public Entity
{
public:
	Map(vector<vector<char>> mapDescription, shared_ptr<TileDrawer> pDrawer);

	void draw(sf::RenderWindow &window) const override;
	void update() override;

	vector<vector<unique_ptr<Tile>>> tiles;
	shared_ptr<TileDrawer> pDrawer;
};