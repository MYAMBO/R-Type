/*
** EPITECH PROJECT, 2025
** *
** File description:
** Script
*/

#ifndef SCRIPT_HPP_
    #define SCRIPT_HPP_

#include "Component.hpp"
#include "World.hpp"

#include <functional>

/**
 * @brief Script component to define the Script of an entity.
 *
 * This component holds the Script factor of an entity.
 * It provides methods to retrieve and modify the Script value.
*/
class Script : public Component {
    public:
        explicit Script(std::function<void(int entityId, World &world)> script = nullptr);
        ~Script() override = default;

        [[nodiscard]] std::function<void(int entityId, World &world)> getScript() const;

        void setScript(std::function<void(int entityId, World &world)> script);
    private:
        std::function<void(int entityId, World &world)> _script;
};

#endif /* !SCRIPT_HPP_ */