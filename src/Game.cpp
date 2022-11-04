#include "Game.hpp"
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

using std::make_unique;

Game::Game()
{
    tmx::Map gameMap;
    gameMap.load("assets/mainMap.tmx");
    const auto &tileSets = gameMap.getTilesets();
    for (auto &ts : tileSets)
    {
        std::string s("Objects");
        if (ts.getName() == s)
        {
            EntityManager::inst().setObjectTileset(ts);
        }
    }

    for (std::size_t i = 0; i < gameMap.getLayers().size(); i++)
    {
        if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Tile)
        {
            mapLayers.push_back(make_unique<MapLayer>(gameMap, i));
        }
        if (gameMap.getLayers()[i]->getType() == tmx::Layer::Type::Object)
        {
            const auto &objectLayer = gameMap.getLayers()[i]->getLayerAs<tmx::ObjectGroup>();
            for (const auto &object : objectLayer.getObjects())
            {
                EntityManager::inst().addObjectAsEntity(object);
            }
        }
    }

    EntityManager::inst().addPlayer("assets/complete_player_modernStyle.png");

    // Add some NPCs
    EntityManager::inst().addRaver(constants::window_width / 3, constants::window_height / 3, "assets/Premade_Character_07.png");
    EntityManager::inst().addRaver(constants::window_width / 3, 2 * constants::window_height / 3, "assets/Premade_Character_07.png");

    // Limit the framerate
    // This allows other processes to run and reduces power consumption
    window.setFramerateLimit(60); // Max rate is 60 frames per second
}

void loadChatBox(tgui::GuiBase &gui)
{
    tgui::Theme theme;
    theme.load("assets/TransparentGrey.txt");

    auto chatbox = tgui::ChatBox::create();
    chatbox->setRenderer(theme.getRenderer("ChatBox"));
    chatbox->setSize(300, 100);
    chatbox->setTextSize(18);
    chatbox->setPosition(420, 310);
    chatbox->setLinesStartFromTop();
    chatbox->addLine("texus: Hey, this is TGUI!", tgui::Color::Green);
    chatbox->addLine("Me: Looks awesome! ;)", tgui::Color::Yellow);
    chatbox->addLine("texus: Thanks! :)", tgui::Color::Green);
    chatbox->addLine("Me: The widgets rock ^^", tgui::Color::Yellow);
    gui.add(chatbox, "InfoBox");
}

// Game loop
// Clear the screen
// Check for user input
// Calculate the updated graphics
// Display the updated graphics
void Game::run()
{
    music.openFromFile("assets/sounds/08. Surrounded.flac");
    tgui::GuiSFML gui{window};
    loadChatBox(gui);
    while (window.isOpen())
    {
        // Clear the screen
        window.clear(sf::Color::Black);
        view.setCenter(EntityManager::inst().getPlayer()->x(), EntityManager::inst().getPlayer()->y());
        window.setView(view);

        // Check for any events since the last loop iteration
        sf::Event event;

        // If the user pressed "Escape", or clicked on "close", we close the window
        // This will terminate the program
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        // Calculate the updated graphics
        EntityManager::inst().update(music);
        EntityManager::inst().handleCollisions();

        for (auto &&layer : mapLayers)
        {
            window.draw(*layer);
        }
        EntityManager::inst().draw(window);
        auto speakers = EntityManager::inst().getSpeakers();
        for (auto &&speaker : speakers)
        {
            auto conn = speaker->field_changed.connect([&gui](Speaker &s, const string &fieldName)
                                                       { gui.get<tgui::ChatBox>("InfoBox")->addLine("Speakers activated"); });
        }
        gui.draw();
        window.display();
    }
}