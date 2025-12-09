/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** BoxCollider
*/


#ifndef R_TYPE_BOXCOLLIDER_HPP
    #define R_TYPE_BOXCOLLIDER_HPP

#include <SFML/Graphics/Text.hpp>

#include "Component.hpp"

/**
 * @brief A BoxCollider component for handling collision detection.
 * This component defines a rectangular collision area for an entity,
 * allowing it to interact with other entities in the game world.
 */
class BoxCollider : public Component {
public:
    explicit BoxCollider(const sf::Vector2f &size);
    ~BoxCollider() override = default;

    [[nodiscard]] bool isVisible() const;
    [[nodiscard]] bool isTrigger() const;
    [[nodiscard]] sf::Vector2f getSize() const;
    [[nodiscard]] sf::Vector2f getOffset() const;

    void setTrigger(bool trigger);
    void setVisibility(bool visible);
    void setSize(const sf::Vector2f &size);
    void setOffset(const sf::Vector2f &offset);

private:
    sf::Vector2f _size;
    sf::Vector2f _offset;
    bool _visible = false;
    bool _trigger = false;
};

#endif //R_TYPE_BOXCOLLIDER_HPP
