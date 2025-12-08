/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Tag
*/


#ifndef TAG_HPP_
    #define TAG_HPP_

#include <iostream>

#include "Component.hpp"

/**
 * @brief Tag component to give a name on an entity and find a specific entity easier.
 *
 * This component encapsulates a tag name.
 * It provides methods to retrieve and modify the tag name.
*/
class Tag : public Component {

    public:
        Tag(const std::string &tag);
        virtual ~Tag() = default;

    [[nodiscard]] std::string getTag() const;

    void setTag(const std::string &tag);

    private:
        std::string _tag;
};

#endif //TAG_HPP_
