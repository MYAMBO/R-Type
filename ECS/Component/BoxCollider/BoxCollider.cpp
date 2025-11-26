/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"

/**
 * @brief Constructs a new BoxCollider component with specify size.
 * @param size The box collider size.
*/
BoxCollider::BoxCollider(sf::Vector2f &size)
    : _size(size), _offset(-size.x / 2.0f, -size.y / 2.0f)
{
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
    return _size;
}

/**
 * @brief Gets the offset value of the box collider.
 * @return The offset value of the box collider.
*/
sf::Vector2f BoxCollider::getOffset() const
{
    return _offset;
}

/**
 * @brief Sets the trigger value of the box collider.
 * @param trigger The new trigger value of the box collider.
*/
void BoxCollider::setTrigger(bool trigger)
{
    _trigger = trigger;
}

/**
 * @brief Sets the visibility value of the box collider.
 * @param visible The new visibility value of the box collider.
*/
void BoxCollider::setVisibility(bool visible)
{
    _visible = visible;
}

/**
 * @brief Sets the size vector of the box collider.
 * @param size The new size vector of the box collider.
*/
void BoxCollider::setSize(const sf::Vector2f &size)
{
    _size = size;
}

/**
 * @brief Sets the offset vector of the box collider.
 * @param offset The new offset vector of the box collider.
*/
void BoxCollider::setOffset(const sf::Vector2f &offset)
{
    _offset = offset;
}
