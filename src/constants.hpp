#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

struct constants
{
  static constexpr int window_width{60 * 16};
  static constexpr int window_height{30 * 16};
  static constexpr int tile_size{16};
  static constexpr float player_speed{1.0f};

  static const unordered_map<char, sf::Vector2<int>> tilePositionsInMap;

  static const unordered_map<string, int> layers;
};
#endif // CONSTANTS_H
