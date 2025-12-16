/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"

/**
 * @brief Constructs a new BoxCollider component with specify size.
 * @param width The box collider width.
 * @param height The box collider height.
*/
BoxCollider::BoxCollider(const float width, const float height)
    : _x(width), _y(height)
{
    if (width <= 0)
        _x = 0.1f;
    if (height <= 0)
        _y = 0.1f;
}

/**
 * @brief Gets the visibility value of the box collider.
 * @return The visibility value of the box collider.
*/
bool BoxCollider::isVisible() const
{
    return _visible;
}

/**
 * @brief Gets the trigger value of the box collider.
 * @return The trigger value of the box collider.
*/
bool BoxCollider::isTrigger() const
{
    return _trigger;
}

/**
 * @brief Gets the size value of the box collider.
 * @return The size value of the box collider.
*/
sf::Vector2f BoxCollider::getSize() const
{
    return {_x, _y};
}

/**
 * @brief Gets the offset value of the box collider.
 * @return The offset value of the box collider.
*/
sf::Vector2f BoxCollider::getOffset() const
{
    return {-_x / 2.f, -_y / 2.f};
}
/**
 * @brief Sets the trigger value of the box collider.
 * @param trigger The new trigger value of the box collider.
*/
void BoxCollider::setTrigger(const bool trigger)
{
    _trigger = trigger;
}

/**
 * @brief Sets the visibility value of the box collider.
 * @param visible The new visibility value of the box collider.
*/
void BoxCollider::setVisibility(const bool visible)
{
    _visible = visible;
}

/**
 * @brief Sets the size vector of the box collider.
 * @param width The new width of the box collider.
 * @param height The new height of the box collider.
*/
void BoxCollider::setSize(const float width, const float height)
{
    _x = width;
    _y = height;

    if (_x <= 0.0f)
        _x = 0.1f;
    if (_y <= 0.0f)
        _y = 0.1f;
}
