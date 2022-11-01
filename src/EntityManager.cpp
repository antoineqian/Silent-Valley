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

void EntityManager::addObjectAsEntity(const tmx::Object &object)
{
    const auto pos = object.getPosition();
    auto tID = object.getTileID();
    auto path = objectTileSet->getTile(tID)->imagePath;
    addTextureFromPath(path);
    sf::Sprite sprite;
    sprite.setTexture(getTextureFromPath(path));
    sprite.setPosition(pos.x, pos.y);

    // TODO: Templatize ?
    if (object.getClass() == string("Speaker"))
    {
        auto ptr = make_shared<Speaker>(1, sprite, object.getName());
        // auto ptr_alias = ptr.get();

        // Get the hash code for the entity object's type
        auto hash = typeid(Speaker).hash_code();
        // Insert the alias pointer into the map
        groupedEntities[hash].emplace_back(ptr);
        // allEntities.push_back(std::move(ptr));
        allEntities.push_back(ptr);
    }
    else
    {
        auto ptr = make_shared<StaticEntity>(1, sprite, object.getName());
        // auto ptr_alias = ptr.get();
        // Get the hash code for the entity object's type
        auto hash = typeid(StaticEntity).hash_code();
        // Insert the alias pointer into the map
        groupedEntities[hash].emplace_back(ptr);
        // allEntities.push_back(std::move(ptr));
        allEntities.push_back(ptr);
    }
}

void EntityManager::addPlayer(string filePath)
{
    addTextureFromPath(filePath);

    auto pPlayer = make_shared<Player>(
        constants::window_width / 2,
        constants::window_height / 2,
        constants::layers.at("main"),
        getTextureFromPath(filePath),
        "Player");
    // auto ptr_alias = pPlayer.get();
    // Get the hash code for the entity object's type
    auto hash = typeid(Player).hash_code();
    groupedEntities[hash].emplace_back(pPlayer);

    // allEntities.push_back(std::move(pPlayer));
    allEntities.push_back(pPlayer);
}

void EntityManager::addRaver(float x, float y, string filePath)
{
    addTextureFromPath(filePath);

    auto pRaver = make_shared<Raver>(
        x,
        y,
        constants::layers.at("main"),
        getTextureFromPath(filePath),
        "Raver");
    // auto pRaver = Raver::create(
    //     x,
    //     y,
    //     constants::layers.at("main"),
    //     getTextureFromPath(filePath),
    //     "Raver");
    // auto ptr_alias = pRaver.get();

    // Get the hash code for the entity object's type
    auto hash = typeid(Raver).hash_code();
    groupedEntities[hash].emplace_back(pRaver);

    allEntities.push_back(pRaver);
}

shared_ptr<Player> EntityManager::getPlayer()
{
    auto hash = typeid(Player).hash_code();
    auto p = groupedEntities[hash][0];
    return dynamic_pointer_cast<Player>(p);
}

vector<shared_ptr<Speaker>> EntityManager::getSpeakers()
{
    auto hash = typeid(Speaker).hash_code();
    auto speakersAsEntities = groupedEntities[hash];
    vector<shared_ptr<Speaker>> speakers(speakersAsEntities.size());

    std::transform(
        speakersAsEntities.begin(),
        speakersAsEntities.end(),
        speakers.begin(),
        [](shared_ptr<Entity> e)
        {
            return dynamic_pointer_cast<Speaker>(e);
        });
    return speakers;
}

vector<shared_ptr<StaticEntity>> EntityManager::getStaticEntities()
{
    auto hash = typeid(StaticEntity).hash_code();
    auto staticEntitiesAsEntities = groupedEntities[hash];
    vector<shared_ptr<StaticEntity>> staticEntities(staticEntitiesAsEntities.size());

    std::transform(
        staticEntitiesAsEntities.begin(),
        staticEntitiesAsEntities.end(),
        staticEntities.begin(),
        [](shared_ptr<Entity> e)
        {
            return dynamic_pointer_cast<StaticEntity>(e);
        });
    return staticEntities;
}

vector<shared_ptr<Raver>> EntityManager::getRavers()
{
    auto hash = typeid(Raver).hash_code();
    auto raversAsEntities = groupedEntities[hash];
    vector<shared_ptr<Raver>> ravers(raversAsEntities.size());

    std::transform(
        raversAsEntities.begin(),
        raversAsEntities.end(),
        ravers.begin(),
        [](shared_ptr<Entity> e)
        {
            return dynamic_pointer_cast<Raver>(e);
        });
    return ravers;
}

void EntityManager::draw(sf::RenderWindow &window)
{
    std::sort(allEntities.begin(), allEntities.end(),
              [](std::shared_ptr<Entity> &p1, std::shared_ptr<Entity> &p2)
              {
                  return *p1 < *p2;
              });

    for (auto &&entity : allEntities)
    {
        window.draw(*entity);
    }
};

void doHandleCollisions(shared_ptr<MovingEntity> e1, shared_ptr<const Entity> e2)
{
    auto e1Box = e1->getHitBox();
    auto e2Box = e2->getHitBox();
    if (e2Box.intersects(e1Box))
    {
        auto eTop = e2Box.top;
        auto eBottom = e2Box.top + e2Box.height;
        auto eLeft = e2Box.left;
        auto eRight = e2Box.left + e2Box.width;
        auto pTop = e1Box.top;
        auto pBottom = e1Box.top + e1Box.height;
        auto pLeft = e1Box.left;
        auto pRight = e1Box.left + e1Box.width;

        auto BTOverlap = eBottom - pTop;
        auto TBOverlap = pBottom - eTop;
        auto RLOverlap = eRight - pLeft;
        auto LROverlap = pRight - eLeft;

        auto currentPos = e1->getPosition();
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
            newY = e2Box.top + e2Box.height - 0.7f * constants::player_height /**Diff between hitbox top and bounding box top*/
                   - 12 /**Diff between top of sprite bounds and top of player bounds*/;

            e1->setPosition({currentPos.x, newY});
        }
        else if (TBOverlap > 0 && TBOverlap < RLOverlap && TBOverlap < LROverlap && TBOverlap < BTOverlap) // Coming mainly down
        {
            // std::cout << "Collision moving down\n";
            newY = e2Box.top - 32;
            e1->setPosition({currentPos.x, newY});
        }
        else if (RLOverlap > 0 && RLOverlap < TBOverlap && RLOverlap < LROverlap && RLOverlap < BTOverlap) // Coming mainly left
        {
            // std::cout << "Collision moving left\n";
            newX = e2Box.left + e2Box.width - 16 * 0.1f;
            e1->setPosition({newX, currentPos.y});
        }
        else if (LROverlap > 0 && LROverlap < TBOverlap && LROverlap < RLOverlap && LROverlap < BTOverlap) // Coming mainly right
        {
            // std::cout << "Collision moving right\n";
            newX = e2Box.left - e1Box.width - /**Diff between player x position and left hitbox */ 16 * 0.1f;
            e1->setPosition({newX, currentPos.y});
        }
    }
}

void EntityManager::handleCollisions()
{
    auto p = getPlayer();
    auto staticEntities = getStaticEntities();
    auto speakers = getSpeakers();
    staticEntities.insert(staticEntities.end(), speakers.begin(), speakers.end());

    auto ravers = getRavers();

    // TODO: Space partitioning
    for (auto &&ptrEntity : staticEntities)
    {
        doHandleCollisions(p, ptrEntity);
        for (auto &&raver : ravers)
        {
            doHandleCollisions(raver, ptrEntity);
        }
    }
    for (auto &&raver : ravers)
    {
        doHandleCollisions(raver, p);
        for (auto &&otherRaver : ravers)
        {
            if (raver != otherRaver)
            {
                doHandleCollisions(otherRaver, raver);
            }
        }
    }
}

void EntityManager::update(sf::Music &music)
{
    getPlayer()->update();
    auto ravers = getRavers();
    for (auto &&raver : ravers)
    {
        raver->update();
    }

    if (soundsystemState() && (music.getStatus() == sf::SoundSource::Status::Paused || music.getStatus() == sf::SoundSource::Status::Stopped))
    {
        music.play();
        for (auto &&raver : ravers)
        {
            raver->changeState(make_unique<GoDance>());
        }
    }
    else if (!soundsystemState() && music.getStatus() == sf::SoundSource::Status::Playing)
    {
        music.pause();
    }
}

bool EntityManager::soundsystemState()
{
    // Speakers are all in the same state;
    auto speaker = getSpeakers()[0];
    return speaker->getState();
}

void EntityManager::playerActionCommand()
{
    auto speakers = getSpeakers();
    bool useSpeakers = false;
    for (auto &&speaker : speakers)
    {
        if (getPlayer()->getFacePosition().intersects(speaker->getHitBox()))
            useSpeakers = true;
    }

    if (useSpeakers)
    {
        for (auto &&speaker : speakers)
        {
            speaker->switchState();
        }
    }
}
