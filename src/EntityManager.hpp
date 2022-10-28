#include <vector>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include <memory>
#include <string>
using std::string;
using std::unique_ptr;

// Singleton class that manages all entities
// Only one tileset for every object
class EntityManager
{
public:
    EntityManager(const EntityManager &) = delete;
    EntityManager &operator=(const EntityManager &) = delete;
    EntityManager(EntityManager &&) = delete;
    EntityManager &operator=(EntityManager &&) = delete;

    static EntityManager &inst();

    void addTextureFromPath(string filePath);
    void addObjectAsEntity(const tmx::Object &object);
    void addPlayer(unique_ptr<Player> pPlayer);
    Player &getPlayer();
    void setObjectTileset(const tmx::Tileset &ts);
    sf::Texture &getTextureFromPath(string filePath);

    void draw(sf::RenderWindow &window);
    void handleCollisions();

private:
    using Entities = std::vector<std::unique_ptr<Entity>>;
    Entities allEntities;
    using entityAliasVector = std::vector<Entity *>;
    std::map<size_t, entityAliasVector> groupedEntities;

    unique_ptr<Player> player;
    using TextureResource = std::map<std::string, std::unique_ptr<sf::Texture>>;
    TextureResource textures;
    unique_ptr<const tmx::Tileset> objectTileSet = nullptr;
    EntityManager();
};