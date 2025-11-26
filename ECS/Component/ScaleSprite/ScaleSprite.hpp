/*
** EPITECH PROJECT, 2025
** *
** File description:
** ScaleSprite
*/

#ifndef SCALESPRITE_HPP_
    #define SCALESPRITE_HPP_

#include "../Component.hpp"

class ScaleSprite : public Component {
    public:
        ScaleSprite(float scale = 1.0f);
        ~ScaleSprite() = default;

        [[nodiscard]] float getScale() const;

        void setScale(float scale);

    private:
        float _scale;
};

#endif /* !SCALESPRITE_HPP_ */