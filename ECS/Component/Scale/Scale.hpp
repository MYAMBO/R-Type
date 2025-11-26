/*
** EPITECH PROJECT, 2025
** *
** File description:
** Scale
*/

#ifndef SCALE_HPP_
    #define SCALE_HPP_

#include "../Component.hpp"

class Scale : public Component {
    public:
        Scale(float scaleX = 1.0f, float scaleY = 1.0f);
        ~Scale() = default;

        [[nodiscard]] float getScaleX() const;
        [[nodiscard]] float getScaleY() const;

        void setScaleX(float scaleX);
        void setScaleY(float scaleY);

    private:
        float _scaleX;
        float _scaleY;
};

#endif /* !SCALE_HPP_ */