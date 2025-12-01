/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_

#include "Component.hpp"

class Position : public Component {
    public:
        Position(float x, float y);
        virtual ~Position() = default;

        [[nodiscard]] float getX() const;
        [[nodiscard]] float getY() const;

        void setX(float x);
        void setY(float y);
        
    private:
        float _x;
        float _y;
};

#endif /* !POSITION_HPP_ */