/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Layer
*/

#include "Layer.hpp"

/**
 * @brief Constructs a new Layer with the layer id.
 * @param id Is the layer number
*/
Layer::Layer(const int id) : _id(id) {}

/**
 * @brief Gets the layer id.
*/
int Layer::getLayerId() const { return _id; }


/**
 * @brief Sets the layer id.
*/
void Layer::setLayerId(const int id) { _id = id; }
