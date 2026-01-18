/*
** EPITECH PROJECT, 2025
** bs
** File description:
** ScriptsSys
*/

#ifndef SCRIPTSYS_HPP_
    #define SCRIPTSYS_HPP_

#include "World.hpp"

/**
* @brief ScriptsSys system responsible for updating ScriptsSys components of entities.
*
* This system iterates through all entities in the world that have a ScriptsSys component
* and updates their view based on the associated entity's position.
*/
class ScriptsSys : public System {
    public:
        ScriptsSys() = default;
        ~ScriptsSys() override = default;

        void update(const float& dt, World &w) override;
};

#endif