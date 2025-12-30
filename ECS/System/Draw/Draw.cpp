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

    // 1. Récupération de TOUTES les entités graphiques
    auto allEntities = w.getEntitiesWithAnyComponent<Sprite, Text, RectangleShape>();
    
    // 2. FILTRAGE : On ne garde que celles de la Scène actuelle
    // Cela évite de trier des objets invisibles (Optimisation majeure)
    std::vector<std::shared_ptr<Entity>> visibleEntities;
    visibleEntities.reserve(allEntities.size()); // Prévient les réallocations mémoire
    
    int currentSceneId = w.getCurrentScene();

    for (const auto& entity : allEntities) {
        auto sceneComp = entity->getComponent<Scene>();
        // Si pas de composant Scene, on affiche par défaut, sinon on vérifie l'ID
        if (!sceneComp || sceneComp->getScene() == currentSceneId) {
            visibleEntities.push_back(entity);
        }
    }

    // 3. TRI : On ne trie que les entités visibles (Peu coûteux)
    std::sort(visibleEntities.begin(), visibleEntities.end(), 
    [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) {
        auto layerA = a->getComponent<Layer>();
        auto layerB = b->getComponent<Layer>();
        
        int idA = layerA ? layerA->getLayerId() : 0; // Layer 0 par défaut
        int idB = layerB ? layerB->getLayerId() : 0;

        return idA < idB; // Petit ID = Dessiné en premier (Fond)
    });

    // 4. RENDU : On itère sur le vecteur DÉJÀ TRIÉ
    for (const auto &entity : visibleEntities) {
        
        auto posComp = entity->getComponent<Position>();
        auto scaleComp = entity->getComponent<Scale>();
        auto rotComp = entity->getComponent<Rotation>();

        // --- GESTION SPRITE ---
        if (auto spriteComp = entity->getComponent<Sprite>()) {
            auto sprite = spriteComp->getSprite();
            if (posComp) sprite->setPosition({posComp->getX(), posComp->getY()});
            if (scaleComp) sprite->setScale({scaleComp->getScale(), scaleComp->getScale()});
            if (rotComp) sprite->setRotation(sf::degrees(rotComp->getRotation()));
            window->draw(*sprite);
        }
        
        // --- GESTION TEXTE ---
        else if (auto textComp = entity->getComponent<Text>()) {
            auto& txt = textComp->getSfText();
            if (posComp) txt.setPosition({posComp->getX(), posComp->getY()});
            if (scaleComp) txt.setScale({scaleComp->getScale(), scaleComp->getScale()});
            // Rotation possible aussi pour le texte si besoin
            window->draw(txt);
        }
        
        // --- GESTION RECTANGLE ---
        else if (auto rectComp = entity->getComponent<RectangleShape>()) {
            auto& shape = rectComp->getShape();
            if (posComp) shape.setPosition({posComp->getX(), posComp->getY()});
            
            // CORRECTION CRITIQUE : Ne change pas la Size, change le Scale !
            if (scaleComp) {
                shape.setScale({scaleComp->getScale(), scaleComp->getScale()});
            }
            // La rotation est aussi possible sur les Shapes
            if (rotComp) shape.setRotation(sf::degrees(rotComp->getRotation()));
            
            window->draw(shape);
        }
    }
}