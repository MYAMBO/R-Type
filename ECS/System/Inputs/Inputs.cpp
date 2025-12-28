/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Inputs.cpp
*/

#include <algorithm>

#include "World.hpp"
#include "Inputs.hpp"

/**
 * @brief Constructs an Inputs object.
 */
Inputs::Inputs()
{
    _pressedKeys.reserve(static_cast<size_t>(KeyboardKey::KEY_COUNT));
    _pressedKeys.clear();
}

/**
 * @brief Updates the input states based on SFML events.
 *
 * @param dt Delta time since last update
 * @param w The world context.
 */
void Inputs::update(const float& dt, World &w)
{
    (void)dt;
    const sf::Event &event = w.getEvent();
    if (const auto* key_pressed = event.getIf<sf::Event::KeyPressed>()) {
        processKeyPress(convertSfKey(key_pressed->code));
    }
    else if (const auto* key_released = event.getIf<sf::Event::KeyReleased>()) {
        processKeyRelease(convertSfKey(key_released->code));
    }
}

/**
 * @brief Checks if a specific key is currently pressed.
 *
 * @param key The key to check.
 * @return true if the key is pressed, false otherwise.
 */
bool Inputs::isKeyPressed(const KeyboardKey key) const
{
    return std::find(_pressedKeys.begin(), _pressedKeys.end(), key) != _pressedKeys.end();
}

/**
 * @brief Processes a key press event.
 *
 * @param key The key that was pressed.
 */
void Inputs::processKeyPress(const KeyboardKey key)
{
    if (key == KeyboardKey::Key_Unknown)
        return;
    if (!isKeyPressed(key)) {
        _pressedKeys.push_back(key);
    }
}

/**
 * @brief Processes a key release event.
 *
 * @param key The key that was released.
 */
void Inputs::processKeyRelease(const KeyboardKey key)
{
    if (key == KeyboardKey::Key_Unknown)
        return;
    auto it = std::remove(_pressedKeys.begin(), _pressedKeys.end(), key);
    if (it != _pressedKeys.end()) {
        _pressedKeys.erase(it, _pressedKeys.end());
    }
}

/**
 * @brief Clears all input states.
 */
void Inputs::clearInputs()
{
    _pressedKeys.clear();
}

/**
 * @brief Converts an SFML keyboard key to a custom KeyboardKey enum.
 *
 * @param key The SFML keyboard key to convert.
 * @return The corresponding KeyboardKey enum value.
 */
KeyboardKey Inputs::convertSfKey(const sf::Keyboard::Key key)
{
    return static_cast<KeyboardKey>(static_cast<int>(key));
}

/**
 * @brief Checks if a specific key is currently released.
 *
 * @param key The key to check.
 * @return true if the key is released, false otherwise.
 */
bool Inputs::isKeyReleased(const KeyboardKey key) const
{
    return std::find(_pressedKeys.begin(), _pressedKeys.end(), key) == _pressedKeys.end();
}