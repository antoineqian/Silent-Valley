#pragma once
#include <vector>
#include <string>
#include "Entity.hpp"
#include "constants.hpp"
using std::string;
using std::vector;

class Map : public Entity
{
public:
	Map(vector<vector<char>> mapDescription, int z);
	Map(string descriptionFilePath, int z);
	void draw(sf::RenderWindow &window) const override;
	void update() override;

	vector<vector<char>> description;
	unordered_map<char, sf::Sprite> sprites;
	sf::Texture groundTexture;
};