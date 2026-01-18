/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Movement
*/

#ifndef MOVEMENT_HPP_
    #define MOVEMENT_HPP_

#include "World.hpp"

/**
* @brief Movement system responsible for updating Movement components of entities.
*
* This system iterates through all entities in the world that have a Movement component
* and updates their view based on the associated entity's position.
*/
class Movement : public System {
    public:
        Movement() = default;
        ~Movement() override = default;

        void update(const float& dt, World &w) override;
};

#endif