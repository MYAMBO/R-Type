/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Draw
*/

#include <algorithm>
#include "Draw.hpp"
#include "Text.hpp"
#include "Scale.hpp"
#include "Scene.hpp"
#include "Layer.hpp"
#include "Sprite.hpp"
#include "Rotation.hpp"
#include "Position.hpp"
#include "RectangleShape.hpp"

/**
 * @brief Updates the draw system by rendering entities ordered by Layer.
 */
void Draw::update(const float& dt, World &w)
{
    (void) dt;
    auto window = w.getWindow();
    if (!window) return;

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
            window->draw(*sprite);
        }

        else if (auto textComp = entity->getComponent<Text>()) {
            auto& txt = textComp->getSfText();
            if (posComp)
                txt.setPosition({posComp->getX(), posComp->getY()});
            if (scaleComp)
                txt.setScale({scaleComp->getScale(), scaleComp->getScale()});
            if (rotComp)
                txt.setRotation(sf::degrees(rotComp->getRotation()));
            window->draw(txt);
        }

        else if (auto rectComp = entity->getComponent<RectangleShape>()) {
            auto& shape = rectComp->getShape();
            if (posComp)
                shape.setPosition({posComp->getX(), posComp->getY()});
            if (scaleComp) {
                shape.setScale({scaleComp->getScale(), scaleComp->getScale()});
            }
            if (rotComp)
                shape.setRotation(sf::degrees(rotComp->getRotation()));
            window->draw(shape);
        }
    }
}