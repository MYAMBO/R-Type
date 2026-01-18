/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Draw.cpp
*/

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


Draw::Draw() : _shaderLoaded(false)
{
    sf::Image img(sf::Vector2u(1, 1), sf::Color::White);
    if (!_whiteTexture.loadFromImage(img))
        throw std::runtime_error("Failed to load image");
}

void Draw::update(const float& dt, World &w)
{
    (void) dt;
    auto window = w.getWindow();
    if (!window)
        return;

    if (!_shaderLoaded) {
        if (!_shader.loadFromFile("../assets/shaders/colorblind.frag", sf::Shader::Type::Fragment))
            throw std::runtime_error("Failed to load fragment");
        _shaderLoaded = true;
    }
    static int modeCheckClock = 0;
    static ColorBlindMode currentMode = ColorBlindMode::Normal;
    if (modeCheckClock++ % 30 == 0) {
        auto settings = GameHelper::getEntityByTag(w, "game_availability_settings");
        if (settings) {
            if (auto data = settings->getComponent<Data>()) {
                std::string modeStr = data->getData("color_blind_mode");
                if (modeStr == "protanopia")
                    currentMode = ColorBlindMode::Protanopia;
                else if (modeStr == "deuteranopia")
                    currentMode = ColorBlindMode::Deuteranopia;
                else if (modeStr == "tritanopia")
                    currentMode = ColorBlindMode::Tritanopia;
                else if (modeStr == "achromatopsia")
                    currentMode = ColorBlindMode::Achromatopsia;
                else
                    currentMode = ColorBlindMode::Normal;
            }
        }
    }

    sf::Shader* shaderPtr = nullptr;
    if (currentMode != ColorBlindMode::Normal) {
        ColorMatrix matrix = GameHelperGraphical::getColorMatrix(currentMode);
        _shader.setUniform("r_mix", sf::Glsl::Vec3(matrix.r[0], matrix.r[1], matrix.r[2]));
        _shader.setUniform("g_mix", sf::Glsl::Vec3(matrix.g[0], matrix.g[1], matrix.g[2]));
        _shader.setUniform("b_mix", sf::Glsl::Vec3(matrix.b[0], matrix.b[1], matrix.b[2]));
        _shader.setUniform("is_enabled", 1.0f);
        _shader.setUniform("texture", sf::Shader::CurrentTexture);
        shaderPtr = &_shader;
    }
    std::map<int, std::vector<std::shared_ptr<Entity>>> layers;
    int currentSceneId = w.getCurrentScene();
    for (auto& entity : w.getEntitiesWithAnyComponent<Sprite, Text, RectangleShape>()) {
        auto sceneComp = entity->getComponent<Scene>();
        if (sceneComp && sceneComp->getScene() != currentSceneId)
            continue;

        auto layerComp = entity->getComponent<Layer>();
        int layerId = layerComp ? layerComp->getLayerId() : 0;
        layers[layerId].push_back(entity);
    }
    for (auto& [layerId, entities] : layers) {
        for (auto& entity : entities) {
            auto posComp = entity->getComponent<Position>();
            if (!posComp)
                continue;

            auto scaleComp = entity->getComponent<Scale>();
            auto rotComp = entity->getComponent<Rotation>();
            float scale = scaleComp ? scaleComp->getScale() : 1.0f;
            float rotation = rotComp ? rotComp->getRotation() : 0.0f;

            if (auto spriteComp = entity->getComponent<Sprite>()) {
                auto sprite = spriteComp->getSprite();
                sprite->setPosition({posComp->getX(), posComp->getY()});
                sprite->setScale({scale, scale});
                sprite->setRotation(sf::degrees(rotation));
                window->draw(*sprite, shaderPtr);
            }
            else if (auto textComp = entity->getComponent<Text>()) {
                auto& txt = textComp->getSfText();
                txt.setPosition({posComp->getX(), posComp->getY()});
                txt.setScale({scale, scale});
                txt.setRotation(sf::degrees(rotation));
                window->draw(txt, shaderPtr);
            }
            else if (auto rectComp = entity->getComponent<RectangleShape>()) {
                auto& shape = rectComp->getShape();
                shape.setPosition({posComp->getX(), posComp->getY()});
                shape.setScale({scale, scale});
                shape.setRotation(sf::degrees(rotation));
                
                if (shaderPtr)
                    shape.setTexture(&_whiteTexture);
                else
                    shape.setTexture(nullptr);
                
                window->draw(shape, shaderPtr);
            }
        }
    }
}