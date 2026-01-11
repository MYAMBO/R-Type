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

        void createKayu();
        void createMyambo();
        void createCamera();
        void createOptions();
        void createCredits();
        void createTguiMenu();
        void createPauseMenu();
        void createTguiOptions();
        void createLevelSelect();
        void createLoadingScreen();
        void createPlayer(uint64_t id = 0);
        void createEnemy(float x, float y, int type, int entityId);
        void createBackground(sf::RenderWindow& window);
        void createBullet(size_t entityId, int x, int y, int type);
        void createMenuButton(const std::string& label, int sceneId, float x, float y, const std::function<void()>& onClick);

        std::shared_ptr<Entity> createStatusText(float y, bool initialState);

        static void createSparks(World &world, float x, float y, int amount);
    private:
        World& _world;
};

#endif