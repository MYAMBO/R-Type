/*
** EPITECH PROJECT, 2025
** *
** File description:
** Rotation
*/

#ifndef ROTATION_HPP_
    #define ROTATION_HPP_

#include "Component.hpp"
#include "Sprite.hpp"

/**
 * @brief Rotation component to define the rotation of an entity.
 *
 * This component holds the rotation angle of an entity in degrees.
 * It provides methods to retrieve and modify the rotation value.
*/
class Rotation : public Component {
    public:
        Rotation(float rotation = 0.0f);
        ~Rotation() override = default;

        [[nodiscard]] float getRotation() const;

        void setRotation(float rotation);

    private:
        float _rotation;
        std::string _type;
};

#endif /* !Rotation_HPP_ */