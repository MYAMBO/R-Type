/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** GuiSystem
*/

#ifndef GUISYSTEM_HPP_
    #define GUISYSTEM_HPP_

    #include <TGUI/Backend/SFML-Graphics.hpp>

    #include "System.hpp"
    #include "GuiWidget.hpp"

/**
 * @brief System to manage GUI widgets using TGUI.
*/
class GuiSystem : public System {
    public:
        GuiSystem(sf::RenderWindow& window);

        void update(const float& dt, World& w) override;
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    private:
        tgui::Gui _gui;
};

#endif /* !GUISYSTEM_HPP_ */