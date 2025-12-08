/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Tag
*/


#include "Tag.hpp"

/**
 * @brief Constructs a new Tag component by creating a new tag name for the entity.
 *
 * @param tag The name of the tag of the entity.
 */
Tag::Tag(std::string &tag) : _tag(tag)
{
}

/**
 * @brief Gets the tag name associated with this component.
 *
 * @return A string to of tag name.
 */
std::string Tag::getTag() const
{
    return _tag;
}

/**
 * @brief Sets the tag name associated with this component.
 *
 * @param tag A string of the new tag name.
 */
void Tag::setTag(const std::string &tag)
{
    _tag = tag;
}