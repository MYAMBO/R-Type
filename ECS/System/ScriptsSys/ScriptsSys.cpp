/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** ScriptsSys
*/

#include "ScriptsSys.hpp"

#include "Script.hpp"
#include "HP.hpp"

/**
* @brief Update the scripts of all entities if they have it in the world
* @param dt Delta time since last update
* @param w Reference to the world containing entities and components
*/
void ScriptsSys::update(const float &dt, World &w)
{
    (void)dt;
    for (auto &entity : w.getAllEntitiesWithComponent<Script>()) {
        auto hp = entity->getComponent<HP>();
        if (hp && hp->getHP() <= 0)
            continue;
        auto scriptComp = entity->getComponent<Script>();
        if (!scriptComp || !scriptComp->getScript())
            continue; 
        scriptComp->getScript()(entity->getId(), w);
    }
}