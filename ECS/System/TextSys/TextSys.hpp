/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextSys
*/

#ifndef TEXTSYSTEM_HPP_
    #define TEXTSYSTEM_HPP_

#include "World.hpp"

class TextSystem : public System {
    public:
        TextSystem() = default;
        ~TextSystem() override = default;

        void update(const float& dt, World &w) override;
};

#endif