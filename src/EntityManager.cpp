#include "EntityManager.hpp"
#include <tmxlite/Map.hpp>

using std::make_unique;

EntityManager &EntityManager::inst()
{
    static EntityManager mgr;
    return mgr;
}

EntityManager::EntityManager()
{
}

void EntityManager::setObjectTileset(const tmx::Tileset &ts)
{
    objectTileSet = make_unique<const tmx::Tileset>(ts);
};

void EntityManager::addTextureFromPath(string filePath)
{
    std::unique_ptr<sf::Texture> newTexture = std::make_unique<sf::Texture>();
    newTexture->loadFromFile(filePath);
    textures.insert(std::make_pair(filePath, std::move(newTexture)));
}

sf::Texture &EntityManager::getTextureFromPath(string filePath)
{
    return *(textures[filePath]);
}

void EntityManager::addObjectAsEntity(const tmx::Object &object)
{
    const auto rec = object.getAABB();
    const auto pos = object.getPosition();
    // std::cout << "Rec dimensions " << rec.top << " " << rec.left << " " << rec.height << " " << rec.width << '\n';
    // std::cout << "Rec pos " << pos.x << " " << pos.y << '\n';
    // std::cout << object.getTileID() << '\n';
    // std::cout << object.getTilesetName() << '\n';

    auto tID = object.getTileID();
    auto path = objectTileSet->getTile(tID)->imagePath;
    EntityManager::inst().addTextureFromPath(path);
    sf::Sprite sprite;
    sprite.setTexture(EntityManager::inst().getTextureFromPath(path));
    sprite.setPosition(pos.x, pos.y);

    entities.push_back(make_unique<StaticEntity>(1, sprite));
}

void EntityManager::addPlayer(unique_ptr<Player> pPlayer)
{
    player = std::move(pPlayer);
}

Player &EntityManager::getPlayer()
{
    return *player;
}

void EntityManager::draw(sf::RenderWindow &window)
{
    for (auto &&entity : entities)
    {
        window.draw(*entity);
    }
    window.draw(*player);
};
