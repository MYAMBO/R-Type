/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
    #define FACTORY_HPP_

    #include <cstdint>
    #include <SFML/Graphics/RenderWindow.hpp>

    #include "GameHelperGraphical.hpp"
    #include "Group.hpp"

class Game; 
class World;

    #include "UIFactory.hpp"
    #include "WorldFactory.hpp"
    #include "EffectFactory.hpp"
    #include "ToolsFactory.hpp"

class IGameNetwork;

class Factory {
    public:
        Factory(World& world);
        ~Factory() = default;

        void createMenu();
        void createKayu();
        void createMyambo();
        void createCamera();
        void createCredits();
        void createGameTools();
        void createPauseMenu();
        void createOptionsMenu();
        void createLevelSelect();
        void createMusicGameplay();
        void createLoadingScreen();
        void createPlayer(uint64_t id = 0, float x = 0.f, float y = 0.f);
        void createBackground(sf::RenderWindow& window);
        void createEnemy(float x, float y, int type, int entityId);
        void createPowerUp(float x, float y, int type, int entityId);
        void createBullet(size_t entityId, int x, int y, int type);
        void createEnemyBullet(size_t entityId, int x, int y);
        void createBackwardEnemyBullet(size_t entityId, int x, int y);
        void createCompanion(uint64_t playerId);
        void createScraps(World &world, float x, float y);
        void createScrapUI(World &world, int index);
        void createScrapUIEmpty(int index) const;
        void createBackGameUI();
        void createLasersCompanion(uint64_t companionId, uint64_t playerId);
        void createLevelCompanionUI();
        void createGameOverScreen();
        void createVictoryScreen();
        void createPlayerHUD();
        void createScoreDisplay();
        void createWaitingMenu(IGameNetwork* network = nullptr);

        void createSparks(World &world, float x, float y, int amount, SceneType scene, int lifeTime = 300);
    private:
        UIFactory _uiFactory;
        WorldFactory _worldFactory;
        EffectFactory _effectFactory;
        ToolsFactory _toolsFactory;
};

#endif