#pragma once
#include "Tile.hpp"

class WalkTile : public Tile
{
public:
	WalkTile(sf::Vector2f position, shared_ptr<TileDrawer> pDrawer);

	void draw(sf::RenderWindow &window) const override;
};