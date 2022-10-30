#include "Human.hpp"
/**
 * @brief Generic non player character class
 *
 */
class Raver : public Human
{
public:
    Raver(float x, float y, int z, sf::Texture &texture, string name);
    ~Raver();
    void update() override;
};