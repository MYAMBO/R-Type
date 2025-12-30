/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** RectangleShape
*/

#ifndef R_TYPE_RECTANGLESHAPE_HPP
    #define R_TYPE_RECTANGLESHAPE_HPP

#include "Component.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

/**
 * @brief RectangleShape component to render simple geometric shapes.
 *
 * This component holds an SFML RectangleShape.
*/
class RectangleShape : public Component {
    public:
        RectangleShape(float width, float height, int red = 255, int green = 255, int blue = 255, int alpha = 255);
        ~RectangleShape() override = default;

        void setSize(float width, float height);

        void setColor(int red, int green, int blue, int alpha);

        [[nodiscard]] sf::RectangleShape& getShape();

        [[nodiscard]] sf::Vector2f getSize() const;

    private:
        sf::RectangleShape _shape;
};

#endif //R_TYPE_RECTANGLESHAPE_HPP