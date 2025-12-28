/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Creator
*/

#ifndef CREATOR_HPP_
    #define CREATOR_HPP_

    #include "World.hpp"
    #include <cstdint>
    #include <memory>
    #include <functional>
    #include <SFML/Graphics/RenderWindow.hpp>

class Creator {
    public:
        Creator(World& world);
        ~Creator() = default;

        void createMenu();
        void createCamera();
        void createOptions();
        void createPlayer(uint64_t id = 0);
        void createEnemy(float x, float y, int type);
        void createBackground(sf::RenderWindow& window);
        void createBullet(size_t entityId, int x, int y, int type);
        void createMenuButton(const std::string& label, int sceneId, float x, float y, const std::function<void()>& onClick);
    private:
        World& _world;
};

#endif