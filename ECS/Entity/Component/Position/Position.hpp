/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Position
*/

#pragma once

#include "../Component.hpp"

class Position : public Component {
    public:
        Position(float x, float y);
        virtual ~Position() = default;

        float getX() const;
        float getY() const;

        void setX(float x);
        void setY(float y);
        
    private:
        float _x;
        float _y;
};
