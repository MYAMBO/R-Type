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

static const std::array<std::string, (static_cast<size_t>(KeyboardKey::KEY_COUNT) + 3)> keyNames = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9",
    "Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu",
    "LBracket", "RBracket", "Semicolon", "Comma", "Period", "Quote", "Slash", "Backslash", "Tilde", "Equal", "Hyphen",
    "Space", "Enter", "Backspace", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete",
    "Add", "Subtract", "Multiply", "Divide",
    "Left", "Right", "Up", "Down",
    "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "Numpad9",
    "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"
};

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
        _lastKeyDetected = convertSfKey(key_pressed->code);
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
 * @brief Checks if a specific key event was triggered.
 *
 * @param event The SFML event to check.
 * @param key The key to check against.
 * @return true if the event corresponds to the specified key being pressed, false otherwise.
 */
bool Inputs::isTriggered(const sf::Event& event, KeyboardKey key) const
{
    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        if (convertSfKey(keyEvent->code) == key)
            return true;
    }
    return false;
}

/**
* @brief Converts a KeyboardKey enum value to its string representation.
 */
std::string Inputs::keyToString(KeyboardKey key) const
{
    int idx = static_cast<int>(key);
    if (idx < 0 || idx >= static_cast<int>(keyNames.size()))
        return "Unknown";
    return keyNames[idx];
}

/**
* @brief Converts a string representation of a key to its KeyboardKey enum value.
*/
KeyboardKey Inputs::stringToKey(const std::string str)
{
    auto it = std::find(keyNames.begin(), keyNames.end(), str);
    if (it != keyNames.end()) {
        return static_cast<KeyboardKey>(std::distance(keyNames.begin(), it));
    }
    return KeyboardKey::Key_Unknown;
}

/**
 * @brief Retrieves and consumes the last detected key press.
 *
 * @return The last detected KeyboardKey, or Key_Unknown if none.
 */
KeyboardKey Inputs::consumeLastKey()
{
    KeyboardKey k = _lastKeyDetected;
    _lastKeyDetected = KeyboardKey::Key_Unknown;
    return k;
}