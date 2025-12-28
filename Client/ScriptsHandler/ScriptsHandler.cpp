/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ScriptsHandler
*/

#include "Tag.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Group.hpp"
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
void createBullet(size_t entityId, World &world, int x, int y, int type)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (entity)
        return;
    bool isPlayer = (type == Bullet);
    auto bullet = world.createEntity(entityId);
    if (isPlayer) {
        bullet->addComponent<Position>(x, y);
        bullet->addComponent<Velocity>(10.f, 0.f);
        bullet->addComponent<Animator>(2, 1, 3.0f, 200, 120, 32, 15, 0, 0);
    } else {
        bullet->addComponent<Position>(x - 20.f , y + 15.f);
        bullet->addComponent<Rotation>(180.f);
        bullet->addComponent<Velocity>(-10.f, 0.f);
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
void backgroundScrollScript(size_t entityId, World &world)
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
void playerfire(size_t entityId, World &world)
{
    auto fire = GameHelper::getEntityById(world, entityId);
    size_t groupId = fire->getComponent<Group>()->getId();
    auto list = GameHelper::getEntitiesByGroup(world, groupId);
    std::shared_ptr<Entity> player = nullptr;
    for (const auto& e : list) {
        if (e->getId() == entityId)
            continue;
        if (e->getComponent<Tag>()->getTag() == "player" || e->getComponent<Tag>()->getTag() == "player_mate")
            player = e;
    }
    auto posPlayer = player->getComponent<Position>();

    if (!fire)
        return;
    auto posFire = fire->getComponent<Position>();
    if (!posFire || !posPlayer)
        return;
    posFire->setX(posPlayer->getX() - 25.f);
    posFire->setY(posPlayer->getY() + 10.f);
}