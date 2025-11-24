/*
** EPITECH PROJECT, 2025
** bs
** File description:
** System
*/

#pragma once

class World;

class System {
    public:
        System() = default;
        virtual ~System() = default;

        virtual void update(const float& dt, World &w) = 0;
    private:
};
