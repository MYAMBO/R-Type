/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** DeathSys
*/

#include "Sprite.hpp"
#include "DeathSys.hpp"

void DeathSys::update(const float &dt, World &world)
{
    (void)dt;
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
        world.killEntity(id);
    }
}