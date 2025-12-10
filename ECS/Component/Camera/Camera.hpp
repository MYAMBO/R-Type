/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Camera
*/


#ifndef R_TYPE_CAMERA_HPP
    #define R_TYPE_CAMERA_HPP

    #include <SFML/Graphics/Text.hpp>
    #include <SFML/Graphics/View.hpp>
    #include <SFML/Graphics/Texture.hpp>

#include "Component.hpp"

/**
 * @brief A Camera component for handling collision detection.
 * This component defines a rectangular collision area for an entity,
 * allowing it to interact with other entities in the game world.
 */
class Camera : public Component {
public:
    Camera(const sf::Vector2f &size = {800.f, 600.f}, const sf::Vector2f &position = {0.f, 0.f});
    virtual ~Camera() = default;


    [[nodiscard]] sf::Vector2f getSize() const;
    [[nodiscard]] sf::Vector2f getPosition() const;
    [[nodiscard]] sf::View& getView();

    void setSize(const sf::Vector2f &size);
    void setPosition(const sf::Vector2f &position);
    void setView(const sf::View& view);

private:
    sf::View _view;
    sf::Vector2f _size;
    sf::Vector2f _position;
};

#endif //R_TYPE_CAMERA_HPP
