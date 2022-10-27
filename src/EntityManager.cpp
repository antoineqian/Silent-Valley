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
    const auto rec = object.getAABB();
    const auto pos = object.getPosition();
    // std::cout << "Rec dimensions " << rec.top << " " << rec.left << " " << rec.height << " " << rec.width << '\n';
    std::cout << object.getName() << '\n';
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
    // auto box = sprite.getGlobalBounds();
    // std::cout << "Box " << box.top << " " << box.height << " " << box.top + box.height << '\n';
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
    std::sort(allEntities.begin(), allEntities.end());

    // auto box = player->getHitBox();
    // std::cout << "Player Box " << box.top << " " << box.height << " " << box.top + box.height << '\n';

    for (auto &&entity : allEntities)
    {
        // if (entity < player)
        // {
        // std::cout << "Drawing " << entity->name << " before player" << '\n';
        window.draw(*entity);
        // }
    }
    // window.draw(*player);
    // for (auto &&entity : allEntities)
    // {
    //     if (entity > player)
    //     {
    //         window.draw(*entity);
    //         // std::cout << "Drawing " << entity->name << " after player" << '\n';
    //     }
    // }
};

// struct InFrontOfComparator
// {
//     inline bool operator()(const unique_ptr<Entity> &e1, const unique_ptr<Entity> &e2
//     {
//         auto box1 = e1->getHitBox();
//         auto box2 = e2->getHitBox();
//         return (box1.top + box1.height > box2.top + box2.height);
//     }
// };

// void EntityManager::prepareRender()
// {
//     for (auto &&entity : entities)
//     {
//         auto box = entity->getHitBox();
//         std::cout << entity->name << " y pos " << box.top + box.height << '\n';
//     }
// }