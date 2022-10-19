#include "Tile.hpp"
#include "TileDrawer.hpp"

Tile::Tile(sf::Vector2f position, shared_ptr<TileDrawer> pDrawer) : position(position), pDrawer(pDrawer)
{
}
sf::Vector2f Tile::getPosition() const { return position; }

void Tile::update()
{
}