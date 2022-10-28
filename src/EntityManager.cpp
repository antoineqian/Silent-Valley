#include "EntityManager.hpp"
#include <tmxlite/Map.hpp>
#include <iostream>
using std::cout;
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
    // const auto rec = object.getAABB();
    const auto pos = object.getPosition();
    // std::cout << "Rec dimensions " << rec.top << " " << rec.left << " " << rec.height << " " << rec.width << '\n';
    // std::cout << object.getName() << '\n';
    // std::cout << "pos " << pos.x << " " << pos.y << '\n';
    // std::cout << "Rec " << rec.top << " " << rec.height << " " << rec.top + rec.height << '\n';
    // std::cout << object.getTileID() << '\n';
    // std::cout << object.getTilesetName() << '\n';

    auto tID = object.getTileID();
    auto path = objectTileSet->getTile(tID)->imagePath;
    EntityManager::inst().addTextureFromPath(path);
    sf::Sprite sprite;
    sprite.setTexture(EntityManager::inst().getTextureFromPath(path));
    sprite.setPosition(pos.x, pos.y);

    auto ptr = make_unique<StaticEntity>(1, sprite, object.getName());
    auto ptr_alias = ptr.get();
    // Get the hash code for the entity object's type
    auto hash = typeid(StaticEntity).hash_code();
    // Insert the alias pointer into the map
    groupedEntities[hash].emplace_back(ptr_alias);
    allEntities.push_back(std::move(ptr));
}

void EntityManager::addPlayer(unique_ptr<Player> pPlayer)
{
    auto ptr_alias = pPlayer.get();
    // Get the hash code for the entity object's type
    auto hash = typeid(Player).hash_code();
    groupedEntities[hash].emplace_back(ptr_alias);

    allEntities.push_back(std::move(pPlayer));
    // player = std::move(pPlayer);
}

Player &EntityManager::getPlayer()
{
    auto hash = typeid(Player).hash_code();
    auto p = groupedEntities[hash][0];
    return *dynamic_cast<Player *>(p);
}

void EntityManager::draw(sf::RenderWindow &window)
{
    std::sort(allEntities.begin(), allEntities.end(),
              [](std::unique_ptr<Entity> &p1, std::unique_ptr<Entity> &p2)
              {
                  return *p1 < *p2;
              });

    for (auto &&entity : allEntities)
    {
        // auto box = entity->getHitBox();
        // std::cout << entity->name << " y pos " << box.top + box.height << '\n';
        window.draw(*entity);
    }
};

void EntityManager::handleCollisions()
{
    auto pHash = typeid(Player).hash_code();
    auto p = dynamic_cast<Player *>(groupedEntities[pHash][0]);
    auto velocity = p->getVelocity();
    auto seHash = typeid(StaticEntity).hash_code();
    auto staticEntities = groupedEntities[seHash];

    for (auto &&ptrEntity : staticEntities)
    {
        auto currentPos = p->getPosition();
        auto entityBox = ptrEntity->getHitBox();
        auto playerBox = p->getHitBox();
        if (entityBox.intersects(playerBox))
        {
            if (std::abs(velocity.x) > 0)
            { // Horizontal movement
                if (velocity.x > 0)
                { // Moving right
                    std::cout << "Collision moving right\n";
                    p->setPosition({entityBox.left - playerBox.width, currentPos.y});
                }
                else
                { // Moving left
                    std::cout << "Collision moving right\n";
                    p->setPosition({entityBox.left + entityBox.width - 16 * 0.1f, currentPos.y});
                }
            }
            auto currentPos = p->getPosition();
            if (std::abs(velocity.y) > 0)
            { // Vertical movement
                if (velocity.y > 0)
                { // Moving down
                    std::cout << "Collision moving down\n";

                    p->setPosition({currentPos.x, entityBox.top - 32});
                }
                else
                { // Moving up
                    std::cout << "Collision moving up\n";
                    std::cout << "EntityBox bottom : " << entityBox.top + entityBox.height
                              << ", PlayerBox top:  " << playerBox.top
                              << ", Player y:" << currentPos.y << '\n';
                    p->setPosition({currentPos.x, entityBox.top + entityBox.height - 0.7f * constants::player_height /**Diff between hitbox top and bounding box top*/
                                                      - 12 /**Diff between top of sprite bounds and top of player bounds*/});
                }
            }
        }
    }
}