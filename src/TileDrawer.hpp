#pragma once
#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "WalkTile.hpp"
#include "BlockTile.hpp"

class TileDrawer
{
public:
	TileDrawer(sf::Sprite &sprite);
	void draw(sf::RenderWindow &window, const Tile *tile);

private:
	sf::Sprite sprite;
};