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
#include <cmath>

/**
 * @brief Rotation component to define the rotation of an entity.
 *
 * This component holds the rotation angle of an entity in degrees.
 * It provides methods to retrieve and modify the rotation value.
*/
class Rotation : public Component {
    public:
        template<typename T>
        Rotation(float rotation = 0.0f);
        ~Rotation() override = default;

        [[nodiscard]] float getRotation() const;

        void setRotation(float rotation);

    private:
        float _rotation;
        std::string _type;
};

/**
 * @brief Constructs a new Rotation component with specified rotation factors.
 * @param rotation The rotation factor for the component. Default is 0.0f.
 * @tparam T The type of the component, used to set the type string.
*/
template<typename T>
Rotation::Rotation(float rotation)
{
    if (std::is_same<T, Sprite>::value)
    rotation = std::fmod(rotation, 360.0f);
    _rotation = rotation;
}

#endif /* !Rotation_HPP_ */