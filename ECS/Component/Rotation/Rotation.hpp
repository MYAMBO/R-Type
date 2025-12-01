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

class Rotation : public Component {
    public:
        template<typename T>
        Rotation(float rotation = 0.0f);
        ~Rotation() = default;

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
        _type = "Sprite";
    for (; rotation >= 360.0f; rotation -= 360.0f);
    for (; rotation < 0.0f; rotation += 360.0f);
    _rotation = rotation;
}

#endif /* !Rotation_HPP_ */