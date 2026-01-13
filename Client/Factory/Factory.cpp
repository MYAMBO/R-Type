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

void Factory::createBackground(sf::RenderWindow& window)
{
    _worldFactory.createBackground(window);
}

void Factory::createEnemy(float x, float y, int type, int entityId)
{
    _worldFactory.createEnemy(x, y, type, entityId);
}

void Factory::createEnemyBullet(size_t entityId, int x, int y)
{
    _worldFactory.createEnemyBullet(entityId, x, y);
}

void Factory::createBullet(size_t entityId, int x, int y, int type)
{
    _worldFactory.createBullet(entityId, x, y, type);
}

void Factory::createSparks(World &world, float x, float y, int amount)
{
    _effectFactory.createSparks(world, x, y, amount);
}