/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** UIFactory
*/

#ifndef UIFACTORY_HPP_
    #define UIFACTORY_HPP_

#include "LanguageHandler.hpp"

class Game;

class UIFactory {
    public:
        explicit UIFactory(World& world);
        ~UIFactory() = default;

        void createMenu() const;
        void createOptionsMenu() const;
        void createLangSelector() const;
        void createLoadingScreen() const;
        void createBackGameUI() const;
        void createScrapUIEmpty(int index) const;
        void createLevelCompanionUI();
    private:
        World& _world;
        std::shared_ptr<LanguageHandler> _languageHandler;
        void _addOptionToggle(const std::string& label, bool& stateValue, uint64_t parentId) const;
        void _addOptionSlider(const std::string& label, float initialValue, uint64_t parentId, std::function<void(float)> onValueChange,  std::function<void(int, World&)> onUpdate = nullptr) const;
        void _addColorBlindCycle(const std::string& label, uint64_t parentId) const;
        void _addKeyBindingRow(const std::string& actionName, uint64_t parentId) const;
};

#endif /* !UIFACTORY_HPP_ */