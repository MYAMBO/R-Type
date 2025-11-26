/*
** EPITECH PROJECT, 2025
** *
** File description:
** ScaleCollider
*/

#ifndef SCALECOLLIDER_HPP_
    #define SCALECOLLIDER_HPP_

#include "../Component.hpp"

class ScaleCollider : public Component {
    public:
        ScaleCollider(float scale = 1.0f);
        ~ScaleCollider() = default;

        [[nodiscard]] float getScale() const;

        void setScale(float scale);

    private:
        float _scale;
};

#endif /* !SCALECOLLIDER_HPP_ */