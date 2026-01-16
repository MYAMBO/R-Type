/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
    #define FACTORY_HPP_

    #include <memory>
    #include <cstdint>
    #include <functional>
    #include <SFML/Graphics/RenderWindow.hpp>

    #include "GameHelper.hpp"
    #include "GameHelperGraphical.hpp"
    #include "ScriptsHandler.hpp"

    #include "HP.hpp"
    #include "Tag.hpp"
    #include "Data.hpp"
    #include "Text.hpp"
    #include "Scale.hpp"
    #include "Layer.hpp"
    #include "Group.hpp"
    #include "Scene.hpp"
    #include "Audio.hpp"
    #include "Music.hpp"
    #include "Sprite.hpp"
    #include "Camera.hpp"
    #include "Button.hpp"
    #include "Script.hpp"
    #include "Damage.hpp"
    #include "Position.hpp"
    #include "Velocity.hpp"
    #include "Animator.hpp"
    #include "Rotation.hpp"
    #include "GuiWidget.hpp"
    #include "SoundEffect.hpp"
    #include "BoxCollider.hpp"
    #include "RectangleShape.hpp"

class Game; 
class World;

    #include "UIFactory.hpp"
    #include "WorldFactory.hpp"
    #include "EffectFactory.hpp"
    #include "ToolsFactory.hpp"

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
        void createLoadingScreen();
        void createPlayer(uint64_t id = 0);
        void createBackground(sf::RenderWindow& window);
        void createEnemy(float x, float y, int type, int entityId);
        void createPowerUp(float x, float y, int type, int entityId);
        void createBullet(size_t entityId, int x, int y, int type);
        void createEnemyBullet(size_t entityId, int x, int y);
        void createCompanion(uint64_t playerId);
        void createScraps(World &world, float x, float y);
        void createScrapUI(World &world, int index);
        void createScrapUIEmpty(int index) const;
        void createBackGameUI();
        void createLasersCompanion(uint64_t companionId, uint64_t playerId);
        void createLevelCompanionUI();
        void createPlayerHUD();

        void createSparks(World &world, float x, float y, int amount, SceneType scene, int lifeTime = 300);
    private:
        UIFactory _uiFactory;
        WorldFactory _worldFactory;
        EffectFactory _effectFactory;
        ToolsFactory _toolsFactory;
};

#endif