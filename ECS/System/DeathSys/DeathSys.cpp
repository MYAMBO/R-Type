/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** DeathSys
*/

#include "DeathSys.hpp"
#include "Animator.hpp"
#include "Sprite.hpp"
#include "Tag.hpp"
#include "GameHelper.hpp"

void DeathSys::update(const float &dt, World &world)
{
    std::vector<uint64_t> entitiesToKill;
    auto entities = world.getAllEntitiesWithComponent<HP>();

    for (const auto& entity : entities) {
        if (!entity)
            continue;
        auto hp = entity->getComponent<HP>();
        if (!hp)
            continue;
        if (hp->getHP() > 0)
            continue;
        if (hp->isAlive()) {
            hp->setAlive(false);
            Packet packet;
            packet.dead(entity->getId());
            _network.sendPacket(packet);
            entitiesToKill.push_back(entity->getId());
        }
    }
    for (auto id : entitiesToKill) {
        auto entity = GameHelper::getEntityById(world, id);
        if (!entity)
            continue;
        auto tag = entity->getComponent<Tag>();
        if (tag && tag->getTag() != "player")
            world.killEntity(id);
    }
}