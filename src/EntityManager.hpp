#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <tmxlite/Map.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include "Speaker.hpp"
#include "Raver.hpp"
#include <memory>
#include <string>
#include <vector>
using std::string;
using std::unique_ptr;
using std::vector;

class Player;
// Singleton class that manages all entities
// Only one tileset for every object
class EntityManager
{
public:
    EntityManager(const EntityManager &) = delete;
    EntityManager &operator=(const EntityManager &) = delete;
    EntityManager(EntityManager &&) = delete;
    EntityManager &operator=(EntityManager &&) = delete;

    // Singleton instance
    static EntityManager &inst();

    void addTextureFromPath(string filePath);
    void setObjectTileset(const tmx::Tileset &ts);
    sf::Texture &getTextureFromPath(string filePath);

    void draw(sf::RenderWindow &window);
    void update(sf::Music &music);
    void handleCollisions();

    void playerActionCommand();
    bool soundsystemState();

    // Entity getters
    shared_ptr<Player> getPlayer();
    vector<shared_ptr<Speaker>> getSpeakers();
    vector<shared_ptr<StaticEntity>> getStaticEntities();
    vector<shared_ptr<Raver>> getRavers();

    // Entity "setters"
    void addObjectAsEntity(const tmx::Object &object);
    void addPlayer(string filePath);
    void addRaver(float x, float y, string filePath);

private:
    using Entities = std::vector<std::shared_ptr<Entity>>;
    Entities allEntities;
    using entityAliasVector = std::vector<std::shared_ptr<Entity>>;
    std::map<size_t, entityAliasVector> groupedEntities;

    unique_ptr<Player> player;
    using TextureResource = std::map<std::string, std::shared_ptr<sf::Texture>>;
    TextureResource textures;
    unique_ptr<const tmx::Tileset> objectTileSet = nullptr;
    EntityManager();
};