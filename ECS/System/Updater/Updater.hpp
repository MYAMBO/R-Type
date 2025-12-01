/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Updater
*/

#pragma once

#include "../../World.hpp"

class Updater : public System {
    public:
        Updater();
        ~Updater() = default;

        void update(const float& dt, World &w) override;
    private:
        void updateSprites(const float& dt, World &w);
        void updateBoxColliders(const float& dt, World &w);
};
