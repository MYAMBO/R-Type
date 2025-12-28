/*
** EPITECH PROJECT, 2025
** bs
** File description:
** CameraSys
*/

#ifndef CAMERASYS_HPP_
    #define CAMERASYS_HPP_

#include "World.hpp"

/**
* @brief CameraSys system responsible for updating CameraSys components of entities.
*
* This system iterates through all entities in the world that have a CameraSys component
* and updates their view based on the associated entity's position.
*/
class CameraSys : public System {
    public:
        CameraSys() = default;
        ~CameraSys() override = default;

        void update(const float& dt, World &w) override;
    private:
};

#endif