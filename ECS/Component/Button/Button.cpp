/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Button
*/

#include "Button.hpp"

/**
* @brief Constructs a new Button component with specified width and height.
* @param width The width of the button.
* @param height The height of the button.
*/
Button::Button(float width, float height) 
    : _width(width), _height(height), _state(IDLE)
{
}
  
/**
* @brief Gets the current state of the button.
* @return The current ButtonState.
 */
ButtonState Button::getState() const
{
    return _state;
}

/**
* @brief Gets the width of the button.
* @return The width of the button.
 */
float Button::getWidth() const
{
    return _width;
}

/**
* @brief Gets the height of the button.
* @return The height of the button.
 */
float Button::getHeight() const
{
    return _height;
}

/**
* @brief Sets the current state of the button.
* @param state The new ButtonState.
 */
void Button::setState(ButtonState state)
{
    _state = state;
}

/**
* @brief Sets the callback function to be called when the button is clicked.
* @param callback The callback function.
*/

void Button::setOnClick(std::function<void()> callback)
{
    _onClick = callback;
}

/**brief Sets the callback function to be called when the button is hovered over.
* @param callback The callback function.
*/
void Button::setOnHover(std::function<void()> callback)
{
    _onHover = callback;
}

/**
 * @brief Calls the onClick callback function if it is set.
 */
void Button::click()
{
    if (_onClick) _onClick();
}

/**
 * @brief Calls the onHover callback function if it is set.
 */
void Button::hover()
{
    if (_onHover) _onHover();
}

/**
 * @brief Sets the texture rectangles for different button states.
 * @param idle The texture rectangle for the idle state.
 * @param hover The texture rectangle for the hover state.
 * @param pressed The texture rectangle for the pressed state.
 */
void Button::setTextureRects(const sf::IntRect& idle, const sf::IntRect& hover, const sf::IntRect& pressed)
{
    _rectIdle = idle;
    _rectHover = hover;
    _rectPressed = pressed;
    _hasTextureRects = true;
}

/**
 * @brief Checks if texture rectangles have been set for the button.
 * @return true if texture rectangles are set, false otherwise.
 */
bool Button::hasTextureRects() const
{
    return _hasTextureRects;
}

/**
 * @brief Gets the texture rectangle for a specific button state.
 * @param s The ButtonState for which to get the texture rectangle.
 * @return The corresponding texture rectangle.
 */
const sf::IntRect& Button::getRect(ButtonState s) const
{
    if (s == HOVER)
        return _rectHover;
    if (s == PRESSED)
        return _rectPressed;
    return _rectIdle;
}


/**
 * @brief Sets the color states for different button states.
 * @param idle The color for the idle state.
 * @param hover The color for the hover state.
 * @param pressed The color for the pressed state.
 */
void Button::setColorStates(const sf::Color& idle, const sf::Color& hover, const sf::Color& pressed)
{
    _idleColor = idle;
    _hoverColor = hover;
    _pressedColor = pressed;
    _useColorFilter = true;
}

/**
 * @brief Checks if color filtering is used for the button.
 * @return true if color filtering is used, false otherwise.
 */
bool Button::useColorFilter() const
{
    return _useColorFilter;
}

/**
 * @brief Gets the color for a specific button state.
 * @param state The ButtonState for which to get the color.
 * @return The corresponding color.
 */
sf::Color Button::getColor(ButtonState state) const
{
    switch (state) {
        case HOVER:
            return _hoverColor;
        case PRESSED:
            return _pressedColor;
        default:
            return _idleColor;
    }
}