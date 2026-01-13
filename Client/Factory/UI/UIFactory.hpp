/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** UIFactory
*/

#ifndef UIFACTORY_HPP_
    #define UIFACTORY_HPP_

class Game;

class UIFactory {
    public:
        UIFactory(World& world);
        ~UIFactory() = default;

        void createMenu();
        void createOptionsMenu();
        void createLoadingScreen();

    private:
        World& _world;
        void _addOptionToggle(const std::string& label, bool& stateValue, uint64_t parentId);
        void _addOptionSlider(const std::string& label, float initialValue, uint64_t parentId, std::function<void(float)> onValueChange,  std::function<void(int, World&)> onUpdate = nullptr);
        void _addColorBlindCycle(const std::string& label, uint64_t parentId);
        void _addKeyBindingRow(const std::string& actionName, uint64_t parentId);
        
        void _addLayoutSpacer(uint64_t parentId, float height);
};

#endif /* !UIFACTORY_HPP_ */