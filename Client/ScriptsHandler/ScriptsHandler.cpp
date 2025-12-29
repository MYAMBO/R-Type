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

#include "Network.hpp"
#include "Packet.hpp"


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

    if (world.getCurrentScene() != entity->getComponent<Scene>()->getScene())
        entity->getComponent<Scene>()->setScene(world.getCurrentScene());
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

/**
 * @brief Changes the scene of an entity to the current world scene.
 *
 * This function updates the scene component of the specified entity
 * to match the current scene of the game world.
 * @param entityId The unique ID of the entity.
 * @param world The game world containing entities and components.
 */
void changeSceneScript(int entityId, World& world)
{
    auto entity = GameHelper::getEntityById(world, entityId);
    if (!entity)
        return;
    entity->getComponent<Scene>()->setScene(world.getCurrentScene());
}