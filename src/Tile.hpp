#pragma once
#include "Entity.hpp"
#include <memory>
using std::shared_ptr;

class TileDrawer;

class Tile : public Entity
{

public:
	Tile(sf::Vector2f position, shared_ptr<TileDrawer> pDrawer);
	void update() override;
	sf::Vector2f getPosition() const;

protected:
	shared_ptr<TileDrawer> pDrawer;
	sf::Vector2f position;
};