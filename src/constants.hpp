#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

struct constants
{
  // TODO: constants::window_width/window_height are actually hardcoded from the map size (loaded in main)
  // We should add objects like vegetation to prevent the player going anywhere near the limit
  // of the map, and its black zone.
  // auto mapSize = gameMap.getBounds();
  // std::cout << mapSize.height << '\n'
  //           << mapSize.width;

  static constexpr int window_width{60 * 16};  // = 960
  static constexpr int window_height{40 * 16}; // = 640
  static constexpr int tile_size{16};
  static constexpr float player_speed{1.0f};

  static const unordered_map<char, sf::Vector2<int>> tilePositionsInMap;

  static const unordered_map<string, int> layers;
};
#endif // CONSTANTS_H
