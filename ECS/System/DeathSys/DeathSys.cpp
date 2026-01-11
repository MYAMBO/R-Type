/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** DeathSys
*/

#include "DeathSys.hpp"
#include "Animator.hpp"
#include "Sprite.hpp"

void DeathSys::update(const float &dt, World &w)
{
    for (uint64_t id : _entitiesToKill) {
        w.killEntity(id);
    }
    _entitiesToKill.clear();

    auto entities = w.getAllEntitiesWithComponent<HP>();

    for (const auto& entity : entities) {
        auto hp = entity->getComponent<HP>();
        if (!hp || hp->getHP() > 0)
            continue;
        hp->setAlive(false);
        uint64_t entityId = entity->getId();

        if (_deathTimers.find(entityId) == _deathTimers.end()) {
            auto sprite = entity->getComponent<Sprite>();
            auto animator = entity->getComponent<Animator>();
            if (sprite && animator) {
                sprite->setTexture("../assets/sprites/r-typesheet1.gif");
                *animator = Animator(8, 8, 0.08f, 120, 283, 16, 16, 8, 0);
            }
            _deathTimers[entityId] = 0.0f;
        }
        _deathTimers[entityId] += dt;
        if (_deathTimers[entityId] >= 5.0f) {
            _entitiesToKill.push_back(entityId);
            _deathTimers.erase(entityId);
        }
    }
}