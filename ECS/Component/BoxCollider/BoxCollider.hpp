/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** BoxCollider
*/


#ifndef R_TYPE_BOXCOLLIDER_HPP
    #define R_TYPE_BOXCOLLIDER_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../Component.hpp"

class BoxCollider : public Component {
public:
    BoxCollider(const sf::Vector2f &size);
    virtual ~BoxCollider() = default;

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
