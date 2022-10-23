#include "constants.hpp"

const unordered_map<char, sf::Vector2<int>> constants::tilePositionsInMap = {{'p', {12, 2}},
                                                                             {'b', {7, 6}},
                                                                             {'a', {2, 13}}};

const unordered_map<string, int> constants::layers = {{"ground", 0}, {"main", 1}};
