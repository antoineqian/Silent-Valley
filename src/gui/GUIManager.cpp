#include "GUIManager.hpp"

// tgui::ChatBox::Ptr loadChatBox(tgui::GuiBase &gui)
// {
//     tgui::Theme theme;
//     theme.load("assets/TransparentGrey.txt");
//     auto chatbox = tgui::ChatBox::create();
//     chatbox->setRenderer(theme.getRenderer("ChatBox"));
//     chatbox->setSize(300, 100);
//     chatbox->setTextSize(18);
//     chatbox->setPosition(420, 310);
//     chatbox->setLinesStartFromTop();
//     chatbox->addLine("texus: Hey, this is TGUI!", tgui::Color::Green);
//     chatbox->addLine("Me: Looks awesome! ;)", tgui::Color::Yellow);
//     chatbox->addLine("texus: Thanks! :)", tgui::Color::Green);
//     chatbox->addLine("Me: The widgets rock ^^", tgui::Color::Yellow);
//     gui.add(chatbox, "InfoBox");
//     return chatbox;
// }

GUIManager::GUIManager(sf::RenderWindow &window) : gui{window}
{
    // loadChatBox(gui);
}