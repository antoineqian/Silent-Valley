#pragma once
#include "Tile.hpp"

class BlockTile : public Tile
{
public:
	BlockTile(sf::Vector2f position, shared_ptr<TileDrawer> pDrawer);
	void draw(sf::RenderWindow &window) const override;
};
