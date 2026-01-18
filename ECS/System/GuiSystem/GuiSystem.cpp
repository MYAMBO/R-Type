/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** GuiSystem
*/

#include <algorithm>
#include "GuiSystem.hpp"
#include "GuiWidget.hpp"
#include "Position.hpp"
#include "Scene.hpp"
#include "Layer.hpp"
#include "GameHelper.hpp"

/**
 * @brief Construct a new Gui System object
 * 
 * @param window Reference to the SFML RenderWindow
 */
GuiSystem::GuiSystem(sf::RenderWindow& window)
    : _gui(window)
{
}

/**
 * @brief Update the GUI system
 * 
 * @param dt Delta time since last update
 * @param w Reference to the World
 */
void GuiSystem::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    sf::View backupView = window.getView();
    window.setView(window.getDefaultView());
    _gui.handleEvent(event);
    window.setView(backupView);
}

/**
 * @brief Update the GUI system
 * 
 * @param dt Delta time since last update
 * @param w Reference to the World
 */

void GuiSystem::update(const float& dt, World& w)
{
    (void)dt;
    auto window = w.getWindow();
    if (!window) return;

    int currentSceneId = w.getCurrentScene();
    
    // --- OPTIMISATION : Bucketing par Layer ---
    // La map trie automatiquement par clé (LayerId)
    std::map<int, std::vector<std::shared_ptr<Entity>>> layers;
    
    auto allGuiEntities = w.getAllEntitiesWithComponent<GuiWidget>();

    for (auto& entity : allGuiEntities) {
        auto guiComp = entity->getComponent<GuiWidget>();
        auto widget = guiComp->getRawWidget();
        if (!guiComp || !widget) continue;

        // 1. GESTION DE LA HIERARCHIE (Attachement unique)
        if (!guiComp->isAttached()) {
            if (guiComp->getParentId() == 0) {
                _gui.add(widget);
            } else {
                auto parent = GameHelper::getEntityById(w, guiComp->getParentId());
                if (parent) {
                    auto parentGui = parent->getComponent<GuiWidget>();
                    auto container = std::dynamic_pointer_cast<tgui::Container>(parentGui->getRawWidget());
                    if (container) container->add(widget);
                } else {
                    _gui.add(widget);
                }
            }
            guiComp->setAttached(true);
        }

        // 2. FILTRAGE PAR SCENE ET VISIBILITÉ
        auto sceneComp = entity->getComponent<Scene>();
        bool inCorrectScene = !sceneComp || sceneComp->getScene() == currentSceneId;

        if (inCorrectScene && guiComp->isVisible()) {
            widget->setVisible(true);
            widget->setEnabled(true);
            
            // On range l'entité dans son tiroir de Layer
            auto layerComp = entity->getComponent<Layer>();
            int layerId = layerComp ? layerComp->getLayerId() : 0;
            layers[layerId].push_back(entity);
        } else {
            widget->setVisible(false);
            widget->setEnabled(false);
        }
    }

    // 3. SYNCHRONISATION ET Z-ORDER (Parcours des tiroirs triés)
    for (auto& [layerId, entities] : layers) {
        for (auto& entity : entities) {
            auto guiComp = entity->getComponent<GuiWidget>();
            auto posComp = entity->getComponent<Position>();
            auto widget = guiComp->getRawWidget();

            // Synchronisation Position
            if (posComp) {
                widget->setPosition(posComp->getX(), posComp->getY());
            }

            // IMPORTANT : On pousse au premier plan dans l'ordre du tri
            widget->moveToFront();
        }
    }

    // 4. RENDU FINAL (Post-process compatible)
    sf::View gameView = window->getView();
    window->setView(window->getDefaultView());
    _gui.draw();
    window->setView(gameView);
}