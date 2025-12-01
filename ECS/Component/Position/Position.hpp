/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_

#include "Component.hpp"

/**
 * @brief Position component to store the coordinates of an entity.
 *
 * This component holds the x and y coordinates representing the position
 * of an entity in a 2D space. It provides methods to retrieve and modify
 * the position values.
*/
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