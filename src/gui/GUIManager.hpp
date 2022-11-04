#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

class GUIManager
{
private:
    tgui::GuiSFML gui;

public:
    GUIManager(sf::RenderWindow &window);
};