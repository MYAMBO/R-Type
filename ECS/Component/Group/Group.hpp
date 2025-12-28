/*
** EPITECH PROJECT, 2025
** bs
** File description:
** Group
*/

#ifndef GROUP_HPP_
    #define GROUP_HPP_

#include "Component.hpp"
#include <cstddef>

/**
 * @brief Group component to associate entities together.
 *
 * This component assigns a numerical ID to an entity, allowing systems
 * to identify and process entities belonging to the same logical group.
*/
class Group : public Component {
    public:
        Group(size_t id);
        ~Group() override = default;

        /**
         * @brief Gets the ID of the group.
         * @return The group ID.
         */
        [[nodiscard]] size_t getId() const;

        /**
         * @brief Sets a new ID for the group.
         * @param id The new group ID.
         */
        void setId(size_t id);
        
    private:
        size_t _id; // L'ID du groupe
};

#endif /* !GROUP_HPP_ */