#include <SFML/Graphics.hpp>

#include <string>

#include "constants.hpp"
using std::make_shared;
using namespace std::literals;

// The main function for the program
int main()
{
    sf::Texture texture;
    texture.loadFromFile("../assets/tiles.png");
    sf::IntRect subRect;
    subRect.left = 12 * constants::tile_size; // of course, you'll have to fill it in with the right values...
    subRect.top = 2 * constants::tile_size;
    subRect.width = constants::tile_size;
    subRect.height = constants::tile_size;
    sf::Sprite sprite(texture, subRect);
    // sf::Sprite atlas;
    // atlas.setTexture(texture);
    // auto pDrawer = make_shared<TileDrawer>(atlas);
    // WalkTile tile(sf::Vector2(0.f, 0.f), pDrawer);

    // Create the game's window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimensions
    // and an std::string with the window title
    // The SFML code is in the sf namespace
    sf::RenderWindow game_window{{constants::window_width, constants::window_height},
                                 "Silent Valley Game"};

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    game_window.setFramerateLimit(60); // Max rate is 60 frames per second

    // Game loop
    // Clear the screen
    // Check for user input
    // Calculate the updated graphics
    // Display the updated graphics
    while (game_window.isOpen())
    {
        // Clear the screen
        game_window.clear(sf::Color::Black);

        // Check for any events since the last loop iteration
        sf::Event event;

        // If the user pressed "Escape", or clicked on "close", we close the window
        // This will terminate the program
        while (game_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                game_window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            game_window.close();

        // Calculate the updated graphics
        // the_background.update();
        // the_ball.update();

        // // Display the updated graphics
        // the_background.draw(game_window);
        game_window.draw(sprite);
        for (int i = 0; i < 100; ++i)
        {
            for (int j = 0; j < 100; ++j)
            {
                sprite.setPosition(i * constants::tile_size, j * constants::tile_size);
                game_window.draw(sprite);
            }
        }
        game_window.display();
    }
}
