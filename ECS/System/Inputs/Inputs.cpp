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
    switch (key) {
        case sf::Keyboard::Key::A : return KeyboardKey::Key_A;
        case sf::Keyboard::Key::B: return KeyboardKey::Key_B;
        case sf::Keyboard::Key::C: return KeyboardKey::Key_C;
        case sf::Keyboard::Key::D: return KeyboardKey::Key_D;
        case sf::Keyboard::Key::E: return KeyboardKey::Key_E;
        case sf::Keyboard::Key::F: return KeyboardKey::Key_F;
        case sf::Keyboard::Key::G: return KeyboardKey::Key_G;
        case sf::Keyboard::Key::H: return KeyboardKey::Key_H;
        case sf::Keyboard::Key::I: return KeyboardKey::Key_I;
        case sf::Keyboard::Key::J: return KeyboardKey::Key_J;
        case sf::Keyboard::Key::K: return KeyboardKey::Key_K;
        case sf::Keyboard::Key::L: return KeyboardKey::Key_L;
        case sf::Keyboard::Key::M: return KeyboardKey::Key_M;
        case sf::Keyboard::Key::N: return KeyboardKey::Key_N;
        case sf::Keyboard::Key::O: return KeyboardKey::Key_O;
        case sf::Keyboard::Key::P: return KeyboardKey::Key_P;
        case sf::Keyboard::Key::Q: return KeyboardKey::Key_Q;
        case sf::Keyboard::Key::R: return KeyboardKey::Key_R;
        case sf::Keyboard::Key::S: return KeyboardKey::Key_S;
        case sf::Keyboard::Key::T: return KeyboardKey::Key_T;
        case sf::Keyboard::Key::U: return KeyboardKey::Key_U;
        case sf::Keyboard::Key::V: return KeyboardKey::Key_V;
        case sf::Keyboard::Key::W: return KeyboardKey::Key_W;
        case sf::Keyboard::Key::X: return KeyboardKey::Key_X;
        case sf::Keyboard::Key::Y: return KeyboardKey::Key_Y;
        case sf::Keyboard::Key::Z: return KeyboardKey::Key_Z;
        case sf::Keyboard::Key::Num0: return KeyboardKey::Key_Num0;
        case sf::Keyboard::Key::Num1: return KeyboardKey::Key_Num1;
        case sf::Keyboard::Key::Num2: return KeyboardKey::Key_Num2;
        case sf::Keyboard::Key::Num3: return KeyboardKey::Key_Num3;
        case sf::Keyboard::Key::Num4: return KeyboardKey::Key_Num4;
        case sf::Keyboard::Key::Num5: return KeyboardKey::Key_Num5;
        case sf::Keyboard::Key::Num6: return KeyboardKey::Key_Num6;
        case sf::Keyboard::Key::Num7: return KeyboardKey::Key_Num7;
        case sf::Keyboard::Key::Num8: return KeyboardKey::Key_Num8;
        case sf::Keyboard::Key::Num9: return KeyboardKey::Key_Num9;
        case sf::Keyboard::Key::LAlt: return KeyboardKey::Key_LAlt;
        case sf::Keyboard::Key::RAlt: return KeyboardKey::Key_RAlt;
        case sf::Keyboard::Key::Menu: return KeyboardKey::Key_Menu;
        case sf::Keyboard::Key::Escape: return KeyboardKey::Key_Escape;
        case sf::Keyboard::Key::LShift: return KeyboardKey::Key_LShift;
        case sf::Keyboard::Key::RShift: return KeyboardKey::Key_RShift;
        case sf::Keyboard::Key::LSystem: return KeyboardKey::Key_LSystem;
        case sf::Keyboard::Key::RSystem: return KeyboardKey::Key_RSystem;
        case sf::Keyboard::Key::LControl: return KeyboardKey::Key_LControl;
        case sf::Keyboard::Key::RControl: return KeyboardKey::Key_RControl;
        case sf::Keyboard::Key::LBracket: return KeyboardKey::Key_LBracket;
        case sf::Keyboard::Key::RBracket: return KeyboardKey::Key_RBracket;
        case sf::Keyboard::Key::Semicolon: return KeyboardKey::Key_SemiColon;
        case sf::Keyboard::Key::Comma: return KeyboardKey::Key_Comma;
        case sf::Keyboard::Key::Slash: return KeyboardKey::Key_Slash;
        case sf::Keyboard::Key::Equal: return KeyboardKey::Key_Equal;
        case sf::Keyboard::Key::Hyphen: return KeyboardKey::Key_Dash;
        case sf::Keyboard::Key::Space: return KeyboardKey::Key_Space;
        case sf::Keyboard::Key::Enter: return KeyboardKey::Key_Enter;
        case sf::Keyboard::Key::Period: return KeyboardKey::Key_Period;
        case sf::Keyboard::Key::Backspace: return KeyboardKey::Key_Backspace;
        case sf::Keyboard::Key::Backslash: return KeyboardKey::Key_BackSlash;
        case sf::Keyboard::Key::Up: return KeyboardKey::Key_Up;
        case sf::Keyboard::Key::Tab: return KeyboardKey::Key_Tab;
        case sf::Keyboard::Key::End: return KeyboardKey::Key_End;
        case sf::Keyboard::Key::Add: return KeyboardKey::Key_Add;
        case sf::Keyboard::Key::Home: return KeyboardKey::Key_Home;
        case sf::Keyboard::Key::Left: return KeyboardKey::Key_Left;
        case sf::Keyboard::Key::Down: return KeyboardKey::Key_Down;
        case sf::Keyboard::Key::Right: return KeyboardKey::Key_Right;
        case sf::Keyboard::Key::Insert: return KeyboardKey::Key_Insert;
        case sf::Keyboard::Key::Delete: return KeyboardKey::Key_Delete;
        case sf::Keyboard::Key::Divide: return KeyboardKey::Key_Divide;
        case sf::Keyboard::Key::PageUp: return KeyboardKey::Key_PageUp;
        case sf::Keyboard::Key::PageDown: return KeyboardKey::Key_PageDown;
        case sf::Keyboard::Key::Subtract: return KeyboardKey::Key_Subtract;
        case sf::Keyboard::Key::Multiply: return KeyboardKey::Key_Multiply;
        case sf::Keyboard::Key::Numpad0: return KeyboardKey::Key_Numpad0;
        case sf::Keyboard::Key::Numpad1: return KeyboardKey::Key_Numpad1;
        case sf::Keyboard::Key::Numpad2: return KeyboardKey::Key_Numpad2;
        case sf::Keyboard::Key::Numpad3: return KeyboardKey::Key_Numpad3;
        case sf::Keyboard::Key::Numpad4: return KeyboardKey::Key_Numpad4;
        case sf::Keyboard::Key::Numpad5: return KeyboardKey::Key_Numpad5;
        case sf::Keyboard::Key::Numpad6: return KeyboardKey::Key_Numpad6;
        case sf::Keyboard::Key::Numpad7: return KeyboardKey::Key_Numpad7;
        case sf::Keyboard::Key::Numpad8: return KeyboardKey::Key_Numpad8;
        case sf::Keyboard::Key::Numpad9: return KeyboardKey::Key_Numpad9;
        case sf::Keyboard::Key::F1 : return KeyboardKey::Key_F1;
        case sf::Keyboard::Key::F2: return KeyboardKey::Key_F2;
        case sf::Keyboard::Key::F3: return KeyboardKey::Key_F3;
        case sf::Keyboard::Key::F4: return KeyboardKey::Key_F4;
        case sf::Keyboard::Key::F5: return KeyboardKey::Key_F5;
        case sf::Keyboard::Key::F6: return KeyboardKey::Key_F6;
        case sf::Keyboard::Key::F7: return KeyboardKey::Key_F7;
        case sf::Keyboard::Key::F8: return KeyboardKey::Key_F8;
        case sf::Keyboard::Key::F9: return KeyboardKey::Key_F9;
        case sf::Keyboard::Key::F10: return KeyboardKey::Key_F10;
        case sf::Keyboard::Key::F11: return KeyboardKey::Key_F11;
        case sf::Keyboard::Key::F12: return KeyboardKey::Key_F12;
        case sf::Keyboard::Key::Pause: return KeyboardKey::Key_Pause;
        default: return KeyboardKey::Key_Unknown;
    }
}