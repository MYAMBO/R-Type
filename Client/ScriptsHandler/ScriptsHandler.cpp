/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ScriptsHandler
*/

#include "Tag.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Inputs.hpp"
#include "Sprite.hpp"
#include "Rotation.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Animator.hpp"
#include "GameHelper.hpp"
#include "ScriptsHandler.hpp"

#include "Network.hpp"
#include "Packet.hpp"

/**
 * @brief Creates a bullet entity.
 *
 * This function initializes a bullet entity with necessary components.
 * @param entityId The ID of the entity that fired the bullet.
 */
void createBullet(int entityId, World &world)
{
    bool isPlayer = false;
    auto shooter = GameHelper::getEntityById(world, entityId);
    if (!shooter)
        std::cerr << "Error: Shooter entity not found." << std::endl;
    if (shooter->getComponent<Tag>()->getTag() == "player" || shooter->getComponent<Tag>()->getTag() == "player_mate")
        isPlayer = true;
    auto bullet = world.createEntity(Side::SERVERSIDE);
    auto shooterPos = shooter->getComponent<Position>();
    if (!shooterPos)
        std::cerr << "Error: Shooter entity has no Position component." << std::endl;
    if (isPlayer) {
        bullet->addComponent<Position>(100 + 60.f, 100 + 15.f);
        bullet->addComponent<Velocity>(15.f, 0.f);
        bullet->addComponent<Animator>(2, 1, 1.5f, 200, 120, 32, 15, 32, 0);
    } else {
        bullet->addComponent<Position>(100 - 20.f , 100 + 15.f);
        bullet->addComponent<Rotation>(180.f);
        bullet->addComponent<Velocity>(-15.f, 0.f);
    }
    bullet->addComponent<Sprite>(std::string("../sprites/r-typesheet1.gif"));
    bullet->addComponent<Scale>(2.f);
    bullet->addComponent<Scene>(1);
    bullet->addComponent<Tag>("bullet");
}

/**
 * @brief Script to scroll the background.
 *
 * This function moves the background entities to create a scrolling effect.
 * @param entityId The ID of the background entity.
 */
void backgroundScrollScript(int entityId, World &world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    auto posComp = entity->getComponent<Position>();
    auto spriteComp = entity->getComponent<Sprite>();
    if (!posComp || !spriteComp)
        return;

    auto bounds = spriteComp->getSprite()->getGlobalBounds();
    float width = bounds.size.x; 
    if (posComp->getX() <= -width)
        posComp->setX(width);
}

/**
 * @brief Updates the position of the player's fire entity.
 *
 * This function aligns the fire entity's position with the player's position.
 * @param entityId The ID of the fire entity.
 * @param world The game world containing entities and components.
 */
void playerfire(int entityId, World &world)
{
    auto player = GameHelper::getEntityById(world, entityId);
    if (!player)
        return;
    auto posPlayer = player->getComponent<Position>();

    auto fire = GameHelper::getEntityById(world, entityId);
    if (!fire)
        return;
    auto posFire = fire->getComponent<Position>();
    if (!posFire || !posPlayer)
        return;
    posFire->setX(posPlayer->getX() - 25.f);
    posFire->setY(posPlayer->getY() + 10.f);
}