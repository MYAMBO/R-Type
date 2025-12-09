/*
** EPITECH PROJECT, 2025
** *
** File description:
** Scale
*/

#ifndef SCALE_HPP_
    #define SCALE_HPP_

#include "Component.hpp"
#include "Sprite.hpp"

/**
 * @brief Scale component to define the scale of an entity.
 *
 * This component holds the scale factor of an entity.
 * It provides methods to retrieve and modify the scale value.
*/
class Scale : public Component {
    public:
        Scale(float scale = 1.0f);
        ~Scale() override = default;

        [[nodiscard]] float getScale() const;

        void setScale(float scale);

    private:
        float _scale;
        std::string _type;
};

#endif /* !SCALE_HPP_ */