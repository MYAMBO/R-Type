/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Updater
*/

#ifndef UPDATER_HPP_
    #define UPDATER_HPP_

    #include "World.hpp"

/**
 * @brief Updater system responsible for updating various components of entities.
 *
 * This system handles the updating of components such as Position, Velocity,
 * Sprite, and BoxCollider for all entities in the world.
*/
class Updater : public System {
    public:
        Updater();
        ~Updater() override = default;

        void update(const float& dt, World &w) override;
    private:
        void updateSprites(const float& dt, World &w);
        void updateCameras(const float& dt, World &w);
        void updateAnimations(const float& dt, World &w);
        void updateBoxColliders(const float& dt, World &w);
};

#endif /* !UPDATER_HPP_ */