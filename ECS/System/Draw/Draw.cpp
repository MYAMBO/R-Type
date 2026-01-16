/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Draw.cpp (DEBUG VERSION)
*/

#include <iostream>
#include <algorithm>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Draw.hpp"
#include "Text.hpp"
#include "Data.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Layer.hpp"
#include "Sprite.hpp"
#include "Rotation.hpp"
#include "Position.hpp"
#include "RectangleShape.hpp"

#include "GameHelper.hpp"
#include "GameHelperGraphical.hpp"

/**
 * @brief Construct a new Draw system object
 */
Draw::Draw() : _shaderLoaded(false)
{
    sf::Image img(sf::Vector2u(1, 1), sf::Color::White);

    if (!_whiteTexture.loadFromImage(img)) {
        std::cerr << "[Draw System] Failed to load white texture for shapes" << std::endl;
    }
}

/**
 * @brief Updates the draw system by rendering entities ordered by Layer.
 */
void Draw::update(const float& dt, World &w)
{
    (void)dt;
    auto window = w.getWindow();
    if (!window) 
        return;

    if (!_shaderLoaded) {
        if (!_shader.loadFromFile("../assets/shaders/colorblind.frag", sf::Shader::Type::Fragment)) {
            std::cerr << "[Draw System] Failed to load shader." << std::endl;
        }
        _shaderLoaded = true;
    }

    ColorBlindMode mode = ColorBlindMode::Normal;
    auto settings = GameHelper::getEntityByTag(w, "game_availability_settings");
    if (settings) {
        auto data = settings->getComponent<Data>();
        if (data) {
            std::string modeStr = data->getData("color_blind_mode");
            if (modeStr == "protanopia") mode = ColorBlindMode::Protanopia;
            else if (modeStr == "deuteranopia") mode = ColorBlindMode::Deuteranopia;
            else if (modeStr == "tritanopia") mode = ColorBlindMode::Tritanopia;
            else if (modeStr == "achromatopsia") mode = ColorBlindMode::Achromatopsia;
            else mode = ColorBlindMode::Normal;
        }
    }

    sf::Shader* shaderPtr = nullptr;
    if (mode != ColorBlindMode::Normal) {
        ColorMatrix matrix = GameHelperGraphical::getColorMatrix(mode);
        _shader.setUniform("r_mix", sf::Glsl::Vec3(matrix.r[0], matrix.r[1], matrix.r[2]));
        _shader.setUniform("g_mix", sf::Glsl::Vec3(matrix.g[0], matrix.g[1], matrix.g[2]));
        _shader.setUniform("b_mix", sf::Glsl::Vec3(matrix.b[0], matrix.b[1], matrix.b[2]));
        _shader.setUniform("is_enabled", 1.0f);
        shaderPtr = &_shader;
    }
    auto allEntities = w.getEntitiesWithAnyComponent<Sprite, Text, RectangleShape>();

    std::vector<std::shared_ptr<Entity>> visibleEntities;
    visibleEntities.reserve(allEntities.size());
    
    int currentSceneId = w.getCurrentScene();

    for (const auto& entity : allEntities) {
        auto sceneComp = entity->getComponent<Scene>();
        if (!sceneComp || sceneComp->getScene() == currentSceneId) {
            visibleEntities.push_back(entity);
        }
    }

    std::sort(visibleEntities.begin(), visibleEntities.end(), 
    [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) {
        auto layerA = a->getComponent<Layer>();
        auto layerB = b->getComponent<Layer>();
        int idA = layerA ? layerA->getLayerId() : 0;
        int idB = layerB ? layerB->getLayerId() : 0;
        return idA < idB;
    });

    for (const auto &entity : visibleEntities) {
        auto posComp = entity->getComponent<Position>();
        auto scaleComp = entity->getComponent<Scale>();
        auto rotComp = entity->getComponent<Rotation>();

        if (auto spriteComp = entity->getComponent<Sprite>()) {
            auto sprite = spriteComp->getSprite();
            if (posComp)
                sprite->setPosition({posComp->getX(), posComp->getY()});
            if (scaleComp)
                sprite->setScale({scaleComp->getScale(), scaleComp->getScale()});
            if (rotComp)
                sprite->setRotation(sf::degrees(rotComp->getRotation()));
            window->draw(*sprite, shaderPtr);
        }

        else if (auto textComp = entity->getComponent<Text>()) {
            auto& txt = textComp->getSfText();
            if (posComp)
                txt.setPosition({posComp->getX(), posComp->getY()});
            if (scaleComp)
                txt.setScale({scaleComp->getScale(), scaleComp->getScale()});
            if (rotComp)
                txt.setRotation(sf::degrees(rotComp->getRotation()));
            window->draw(txt, shaderPtr);
        }

        else if (auto rectComp = entity->getComponent<RectangleShape>()) {
            auto& shape = rectComp->getShape();
            if (posComp)
                shape.setPosition({posComp->getX(), posComp->getY()});
            if (scaleComp)
                shape.setScale({scaleComp->getScale(), scaleComp->getScale()});
            if (rotComp)
                shape.setRotation(sf::degrees(rotComp->getRotation()));
            if (shaderPtr) {
                shape.setTexture(&_whiteTexture);
            } else {
                shape.setTexture(nullptr);
            }
            window->draw(shape, shaderPtr);
        }
    }
}