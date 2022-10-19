#include "BlockTile.hpp"
#include "TileDrawer.hpp"

BlockTile::BlockTile(sf::Vector2f position, shared_ptr<TileDrawer> pDrawer)
	: Tile(position, pDrawer)
{
}

void BlockTile::draw(sf::RenderWindow &window) const
{
	pDrawer->draw(window, this);
}
