/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Camera
*/

#include "Camera.hpp"

/**
 * @brief Constructs a new Camera component with specified size and position.
 *
 * @param size The size of the camera view.
 * @param position The position of the camera view.
 */
Camera::Camera(const sf::Vector2f &size, const sf::Vector2f &position)
    : _size(size), _position(position), _view(sf::FloatRect({position.x, position.y}, {size.x, size.y}))
{
    _view.setSize(size);
    _view.setCenter(position + (size / 2.0f));
}

/**
 * @brief Gets the size of the camera view.
 *
 * @return The size of the camera view.
 */
sf::Vector2f Camera::getSize() const
{
    return _size;
}

/**
 * @brief Gets the position of the camera view.
 *
 * @return The position of the camera view.
 */
sf::Vector2f Camera::getPosition() const
{
    return _position;
}

/**
 * @brief Sets the size of the camera view.
 *
 * @param size The new size of the camera view.
 */
void Camera::setSize(const sf::Vector2f &size)
{
    _size = size;
    _view.setSize(size);
}

/**
 * @brief Sets the position of the camera view.
 *
 * @param position The new position of the camera view.
 */
void Camera::setPosition(const sf::Vector2f &position)
{
    _position = position;
    _view.setCenter(position + (_size / 2.0f));
}

/**
 * @brief Gets the SFML view associated with this camera.
 *
 * @return A reference to the SFML view.
 */
sf::View& Camera::getView()
{
    return _view;
}

/**
 * @brief Sets the SFML view associated with this camera.
 *
 * @param view The new SFML view.
 */
void Camera::setView(const sf::View& view)
{
    _view = view;
}