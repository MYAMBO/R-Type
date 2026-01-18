/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** Factory
*/

#include "Factory.hpp"
#include "Game.hpp"

Factory::Factory(World& world)  :
    _uiFactory(world), _worldFactory(world),
    _effectFactory(world), _toolsFactory(world)
{
}

void Factory::createKayu()
{
    _effectFactory.createKayu();
}

void Factory::createMyambo()
{
    _effectFactory.createMyambo();
}

void Factory::createCamera()
{
    _worldFactory.createCamera();
}

void Factory::createOptionsMenu()
{
    _uiFactory.createOptionsMenu();
}

void Factory::createCredits()
{
    _effectFactory.createCredits();
}

void Factory::createMenu()
{
    _uiFactory.createMenu();
}
void Factory::createGameTools()
{
    _toolsFactory.createGameTools();
}

void Factory::createLoadingScreen()
{
    _uiFactory.createLoadingScreen();
}

void Factory::createPlayer(uint64_t id)
{
    _worldFactory.createPlayer(static_cast<int>(id));
}

void Factory::createEnemy(float x, float y, int type, int entityId)
{
    _worldFactory.createEnemy(x, y, type, entityId);
}

void Factory::createPowerUp(float x, float y, int type, int entityId)
{
    _worldFactory.createPowerUp(x, y, type, entityId);
}

void Factory::createEnemyBullet(size_t entityId, int x, int y)
{
    _worldFactory.createEnemyBullet(entityId, x, y);
}

void Factory::createBackwardEnemyBullet(size_t entityId, int x, int y)
{
    _worldFactory.createBackwardEnemyBullet(entityId, x, y);
}

void Factory::createBullet(size_t entityId, int x, int y, int type)
{
    _worldFactory.createBullet(entityId, x, y, type);
}

void Factory::createSparks(World &world, float x, float y, int amount, SceneType scene, int lifeTime)
{
    _effectFactory.createSparks(world, x, y, amount, scene, lifeTime);
}

void Factory::createCompanion(uint64_t playerId)
{
    _worldFactory.createCompanion(playerId);
}

void Factory::createScraps(World &world, float x, float y)
{
    _worldFactory.createScraps(world, x, y);
}

void Factory::createScrapUI(World &world, int index)
{
    _worldFactory.createScrapUI(world, index);
}

void Factory::createScrapUIEmpty(int index) const
{
    _uiFactory.createScrapUIEmpty(index);
}

void Factory::createBackGameUI()
{
    _uiFactory.createBackGameUI();
}

void Factory::createLasersCompanion(uint64_t companionId, uint64_t playerId)
{
    _worldFactory.createLasersCompanion(companionId, playerId);
}

void Factory::createLevelCompanionUI()
{
    _uiFactory.createLevelCompanionUI();
}

void Factory::createGameOverScreen()
{
    _uiFactory.createGameOverScreen();
}

void Factory::createVictoryScreen()
{
    _uiFactory.createVictoryScreen();
}

void Factory::createPlayerHUD()
{
    _uiFactory.createPlayerHUD();
}

void Factory::createScoreDisplay()
{
    _uiFactory.createScoreDisplay();

}

void Factory::createMusicGameplay()
{
    _worldFactory.createMusicGameplay();
}

void Factory::createWaitingMenu(IGameNetwork* network)
{
    _uiFactory.createWaitingMenu(network);
}