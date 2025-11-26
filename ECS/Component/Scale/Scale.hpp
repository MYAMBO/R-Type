/*
** EPITECH PROJECT, 2025
** *
** File description:
** Scale
*/

#ifndef SCALE_HPP_
    #define SCALE_HPP_

#include "../Component.hpp"
#include "../Sprite/Sprite.hpp"

class Scale : public Component {
    public:
        template<typename T>
        Scale(float scale = 1.0f);
        ~Scale() = default;

        [[nodiscard]] float getScale() const;

        void setScale(float scale);

    private:
        float _scale;
        std::string _type;
};

/**
 * @brief Constructs a new Scale component with specified scale factors.
 * @param scale The scale factor for the sprite. Default is 1.0f.
 * @tparam T The type of the component, used to set the type string.
*/
template<typename T>
Scale::Scale(float scale)
    : _scale(scale)
{
    if (std::is_same<T, Sprite>::value)
        _type = "Sprite";
}

#endif /* !SCALE_HPP_ */