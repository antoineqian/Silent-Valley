#include "EntityManager.hpp"
#include <tmxlite/Map.hpp>
#include <iostream>
#include <algorithm>
using std::cout;
using std::make_shared;
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

// void EntityManager::addNPCEntity(string filePath)
// {
// }

void EntityManager::addObjectAsEntity(const tmx::Object &object)
{
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

void EntityManager::addPlayer(string filePath)
{
    EntityManager::inst().addTextureFromPath(filePath);
    auto animations = AnimationAdapter::getAnimations(EntityManager::inst().getTextureFromPath(filePath));
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, true);
    animatedSprite.setPosition(constants::window_width / 2,
                               constants::window_height / 2);

    auto pPlayer = make_unique<Player>(
        constants::layers.at("main"),
        animatedSprite,
        animations,
        "Player");
    auto ptr_alias = pPlayer.get();
    // Get the hash code for the entity object's type
    auto hash = typeid(Player).hash_code();
    groupedEntities[hash].emplace_back(ptr_alias);

    allEntities.push_back(std::move(pPlayer));
}

// void EntityManager::addPlayer(unique_ptr<Player> pPlayer)
// {
//     auto ptr_alias = pPlayer.get();
//     // Get the hash code for the entity object's type
//     auto hash = typeid(Player).hash_code();
//     groupedEntities[hash].emplace_back(ptr_alias);

//     allEntities.push_back(std::move(pPlayer));
// }

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
        window.draw(*entity);
    }
};

void EntityManager::handleCollisions()
{
    auto pHash = typeid(Player).hash_code();
    auto p = dynamic_cast<Player *>(groupedEntities[pHash][0]);
    auto seHash = typeid(StaticEntity).hash_code();
    auto staticEntities = groupedEntities[seHash];

    for (auto &&ptrEntity : staticEntities)
    {
        auto entityBox = ptrEntity->getHitBox();
        auto playerBox = p->getHitBox();
        if (entityBox.intersects(playerBox))
        {
            auto eTop = entityBox.top;
            auto eBottom = entityBox.top + entityBox.height;
            auto eLeft = entityBox.left;
            auto eRight = entityBox.left + entityBox.width;
            auto pTop = playerBox.top;
            auto pBottom = playerBox.top + playerBox.height;
            auto pLeft = playerBox.left;
            auto pRight = playerBox.left + playerBox.width;

            auto BTOverlap = eBottom - pTop;
            auto TBOverlap = pBottom - eTop;
            auto RLOverlap = eRight - pLeft;
            auto LROverlap = pRight - eLeft;

            auto currentPos = p->getPosition();
            float newX = currentPos.x;
            float newY = currentPos.y;

            // TODO: The direction of the collision is defined by which Overlap is
            // the minimum overlap greater than 0.
            // Potential refactor. (sort sorts in place, so lower_bounds always points to the first element)
            // vector<float> overlaps{BTOverlap, TBOverlap, RLOverlap, LROverlap};
            // std::sort(overlaps.begin(), overlaps.end());
            // auto lower = std::lower_bound(overlaps.begin(), overlaps.end(), 0);
            // std::cout << BTOverlap << " " << TBOverlap << " " << RLOverlap << " " << LROverlap << '\n';
            // std::cout << *lower << '\n';
            // std::cout << std::distance(overlaps.begin(), lower) << '\n';

            if (BTOverlap > 0 && BTOverlap < RLOverlap && BTOverlap < LROverlap && BTOverlap < TBOverlap) // Coming mainly up, even if some diagonal movement is involved
            {
                // std::cout << "Collision moving up\n";
                newY = entityBox.top + entityBox.height - 0.7f * constants::player_height /**Diff between hitbox top and bounding box top*/
                       - 12 /**Diff between top of sprite bounds and top of player bounds*/;

                p->setPosition({currentPos.x, newY});
            }
            else if (TBOverlap > 0 && TBOverlap < RLOverlap && TBOverlap < LROverlap && TBOverlap < BTOverlap) // Coming mainly down
            {
                // std::cout << "Collision moving down\n";
                newY = entityBox.top - 32;
                p->setPosition({currentPos.x, newY});
            }
            else if (RLOverlap > 0 && RLOverlap < TBOverlap && RLOverlap < LROverlap && RLOverlap < BTOverlap) // Coming mainly left
            {
                // std::cout << "Collision moving left\n";
                newX = entityBox.left + entityBox.width - 16 * 0.1f;
                p->setPosition({newX, currentPos.y});
            }
            else if (LROverlap > 0 && LROverlap < TBOverlap && LROverlap < RLOverlap && LROverlap < BTOverlap) // Coming mainly right
            {
                // std::cout << "Collision moving right\n";
                newX = entityBox.left - playerBox.width - /**Diff between player x position and left hitbox */ 16 * 0.1f;
                p->setPosition({newX, currentPos.y});
            }
        }
    }
}