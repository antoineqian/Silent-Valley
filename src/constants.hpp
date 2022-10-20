#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>

#include <unordered_map>
using std::unordered_map;

struct constants
{
  static constexpr int window_width{520};
  static constexpr int window_height{450};
  static constexpr int tile_size{16};
  static const unordered_map<char, sf::Vector2<int>> tilePositionsInMap;
};

#endif // CONSTANTS_H
