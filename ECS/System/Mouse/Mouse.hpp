/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
    #define MOUSE_HPP_

#include "World.hpp"

class Mouse : public System {
    public:
        Mouse() = default;
        ~Mouse() override = default;

        void update(const float& dt, World &world) override;
};

#endif /* !MOUSE_HPP_ */