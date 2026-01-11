/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** RectangleShape
*/

#include "RectangleShape.hpp"

/**
* @brief Construct a new Rectangle Shape component.
* @param width The width of the rectangle.
* @param height The height of the rectangle.
* @param red The red component of the fill color (0-255).
* @param green The green component of the fill color (0-255).
* @param blue The blue component of the fill color (0-255).
* @param alpha The alpha component of the fill color (0-255).
*/
RectangleShape::RectangleShape(float width, float height, int red, int green, int blue, int alpha)
{
    _shape.setSize({width, height});
    if (red < 0)
        red = 0;
    if (red > 255)
        red = 255;
    if (green < 0)
        green = 0;
    if (green > 255)
        green = 255;
    if (blue < 0)
        blue = 0;
    if (blue > 255)
        blue = 255;
    if (alpha < 0)
        alpha = 0;
    if (alpha > 255)
        alpha = 255;
    _shape.setFillColor(sf::Color(red, green, blue, alpha));
}

/**
* @brief Sets the size of the rectangle.
* @param width New width.
* @param height New height.
*/
void RectangleShape::setSize(float width, float height)
{
    _shape.setSize({width, height});
}

/**
* @brief Sets the fill color of the rectangle.
* @param red The red component of the fill color (0-255).
* @param green The green component of the fill color (0-255).
* @param blue The blue component of the fill color (0-255).
* @param alpha The alpha component of the fill color (0-255).
*/
void RectangleShape::setColor(int red, int green, int blue, int alpha)
{
    _shape.setFillColor(sf::Color(red, green, blue, alpha));
}

/**
* @brief Gets the internal SFML RectangleShape (for drawing).
* @return Reference to the SFML shape.
*/
sf::RectangleShape& RectangleShape::getShape()
{
    return _shape;
}

/**
* @brief Gets the size of the rectangle.
* @return The size as a Vector2f.
*/
sf::Vector2f RectangleShape::getSize() const
{
    return _shape.getSize();
}

/**
* @brief Gets the fill color of the rectangle.
* @return The fill color as an SFML Color.
*/
sf::Color RectangleShape::getColor() const
{
    return _shape.getFillColor();
}