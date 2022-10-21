#include <SFML/Graphics.hpp>

#include <string>
#include "Map.hpp"
#include "Player.hpp"
using std::make_shared;
using namespace std::literals;

// The main function for the program
int main()
{
    Map map("../assets/layer0.txt");
    Player player(0, 0);

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
        map.update();
        player.update();

        map.draw(game_window);
        player.draw(game_window);
        game_window.display();
    }
}
