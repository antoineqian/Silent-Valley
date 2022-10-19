#include "WalkTile.hpp"
#include "TileDrawer.hpp"

WalkTile::WalkTile(sf::Vector2f position, shared_ptr<TileDrawer> pDrawer) : Tile(position, pDrawer)
{
}

void WalkTile::draw(sf::RenderWindow &window) const
{
	pDrawer->draw(window, this);
}
