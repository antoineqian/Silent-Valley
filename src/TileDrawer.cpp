#include "TileDrawer.hpp"

// TODO: Make TileDrawer into abstract class with a concrete implementation for each TileAtlas
// Currently the TileDrawer is hardcoded for a known sprite.

TileDrawer::TileDrawer(sf::Sprite &sprite) : sprite(sprite)
{
}

void TileDrawer::draw(sf::RenderWindow &window, const Tile *tile)
{
	// jngl::pushMatrix();
	// jngl::translate(tile->getPosition());
	sprite.setPosition(tile->getPosition());
	const WalkTile *w;
	if ((w = dynamic_cast<const WalkTile *>(tile)))
	{
		// sprite.drawClipped({12.0 / 13, 2.0 / 10}, {1, 3.0 / 10});
		window.draw(sprite);
	}
	const BlockTile *b;
	if ((b = dynamic_cast<const BlockTile *>(tile)))
	{
		// sprite.drawClipped({5.0 / 13, 0}, {6.0 / 13, 1.0 / 10});
		window.draw(sprite);
	}
}