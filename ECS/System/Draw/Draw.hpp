/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#ifndef DRAW_HPP_
    #define DRAW_HPP_

    #include "World.hpp"
    #include <SFML/Graphics/Shader.hpp>
    #include <SFML/Graphics/RenderTexture.hpp>

/**
 * @brief Draw system responsible for rendering entities with Sprite components.
 *
 * This system iterates through all entities in the world that have a Sprite component
 * and draws them to the render window.
*/
class Draw : public System {
    public:
        Draw();
        ~Draw() override = default;

        void update(const float& dt, World &w) override;
    private:
        sf::Shader _shader;
        bool _shaderLoaded = false;
        sf::Texture _whiteTexture;
};

#endif