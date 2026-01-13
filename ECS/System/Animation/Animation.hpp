/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
    #define ANIMATION_HPP_

#include "World.hpp"

/**
 * @brief Animation system responsible for updating Animator components of entities.
 * This system iterates through all entities in the world that have an Animator component
 * and updates their animation frames based on the elapsed time.
*/
class Animation : public System {
    public:
        Animation() = default;
        ~Animation() override = default;

        void update(const float& dt, World &w) override;
    private:
};

#endif