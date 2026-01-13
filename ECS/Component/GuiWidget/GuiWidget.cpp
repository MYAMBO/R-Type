/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** GuiWidget
*/
#include "GuiWidget.hpp"

/**
 * @brief Construct a new GuiWidget component.
 * 
 * @param type The type of the widget
 * @param content The initial content (text) of the widget
 * @param parentId The ID of the parent widget/entity
 */
GuiWidget::GuiWidget(WidgetType type, const std::string& content, uint64_t parentId)
    : _type(type), _parentId(parentId)
{
    switch (type) {
        case WidgetType::LABEL:             _widget = tgui::Label::create(content);     break;
        case WidgetType::BUTTON:            _widget = tgui::Button::create(content);    break;
        case WidgetType::PANEL:             _widget = tgui::Panel::create();            break;
        case WidgetType::VERTICAL_LAYOUT:   _widget = tgui::VerticalLayout::create();   break;
        case WidgetType::HORIZONTAL_LAYOUT: _widget = tgui::HorizontalLayout::create(); break;
        case WidgetType::EDIT_BOX:          _widget = tgui::EditBox::create();          break;
        case WidgetType::CHECKBOX:          _widget = tgui::CheckBox::create();         break;
        case WidgetType::SLIDER:            _widget = tgui::Slider::create();           break;
        case WidgetType::SCROLLABLE_PANEL: _widget = tgui::ScrollablePanel::create();   break;
        default:                            _widget = tgui::ClickableWidget::create();  break;
    }
}

/**
* @brief Set the size of the widget.
* 
* @param w Width of the widget
* @param h Height of the widget
*/
void GuiWidget::setSize(float w, float h)
{
    _widget->setSize(w, h);
}

void GuiWidget::setSize(const std::string& w, const std::string& h)
{
    _widget->setSize(w.c_str(), h.c_str());
}

/**
* @brief Set the position of the widget.
* @param x X position
* @param y Y position
*/
void GuiWidget::setPosition(float x, float y)
{
    _widget->setPosition(x, y);
}

/**
* @brief Set the position of the widget using strings (e.g., "50%", "center").
* @param x X position as string
* @param y Y position as string
 */
void GuiWidget::setPosition(const std::string& x, const std::string& y)
{
    _widget->setPosition(x.c_str(), y.c_str());
}

/**
 * @brief Set the scale of the widget.
 * 
 * @param x X scale factor
 * @param y Y scale factor
 */
void GuiWidget::setScale(float x, float y)
{
    _widget->setScale({x, y});
}

/**
 * @brief Set the visibility of the widget.
 * 
 * @param visible True to make visible, false to hide
 */
void GuiWidget::setVisible(bool visible)
{
    _isVisible = visible;
}

/**
* @brief Set the text size of the widget.
* @param size The text size to set
*/
float GuiWidget::getTextSize() const
{
    if (auto w = std::dynamic_pointer_cast<tgui::Label>(_widget))
        return w->getTextSize();
    else if (auto w = std::dynamic_pointer_cast<tgui::Button>(_widget))
        return w->getTextSize();
    else if (auto w = std::dynamic_pointer_cast<tgui::EditBox>(_widget))
        return w->getTextSize();
    return 0.0f;
}

/**
 * @brief Get the scale of the widget.
 * @return The current scale of the widget
 */
sf::Vector2f GuiWidget::getScale() const
{
    return {_widget->getScale().x, _widget->getScale().y};
}

/**
 * @brief Set auto size for Label widgets.
 * @param autoSize True to enable auto size, false otherwise
 */
void GuiWidget::setAutoSize(bool autoSize)
{
    if (auto w = std::dynamic_pointer_cast<tgui::Label>(_widget))
        w->setAutoSize(autoSize);
}

/**
 * @brief Enable or disable the widget.
 * 
 * @param enabled True to enable, false to disable
 */
void GuiWidget::setEnabled(bool enabled)
{
    _widget->setEnabled(enabled);
}

/**
 * @brief Set the origin of the widget.
 * @param x X origin
 * @param y Y origin
 */
void GuiWidget::setOrigin(float x, float y)
{
    _widget->setOrigin(x, y);

}

/**
 * @brief Set focus to the widget.
 */
void GuiWidget::setFocus()
{
    _widget->setFocused(true);
}

/**
* @brief Set the text of the widget.
* @param text The text to set
 */
void GuiWidget::setText(const std::string& text)
{
    if (auto w = std::dynamic_pointer_cast<tgui::Label>(_widget))
        w->setText(text);
    else if (auto w = std::dynamic_pointer_cast<tgui::Button>(_widget))
        w->setText(text);
    else if (auto w = std::dynamic_pointer_cast<tgui::EditBox>(_widget))
        w->setText(text);
    else if (auto w = std::dynamic_pointer_cast<tgui::CheckBox>(_widget))
        w->setText(text);
}

/**
* @brief Set the text size of the widget.
* @param size The text size to set
 */
void GuiWidget::setTextSize(unsigned int size)
{
    if (auto w = std::dynamic_pointer_cast<tgui::Label>(_widget))
        w->setTextSize(size);
    else if (auto w = std::dynamic_pointer_cast<tgui::Button>(_widget))
        w->setTextSize(size);
    else if (auto w = std::dynamic_pointer_cast<tgui::EditBox>(_widget))
        w->setTextSize(size);
}

/**
 * @brief Set the text color of the widget.
 * @param color The color to set
 */
void GuiWidget::setTextColor(sf::Color color)
{
    _widget->getRenderer()->setProperty("TextColor", tgui::Color(color.r, color.g, color.b, color.a));
}

/**
 * @brief Set the text style of the widget.
 * @param style The text style to set (e.g., Bold, Italic)
 */
void GuiWidget::setTextStyle(tgui::TextStyle style)
{
    if (auto w = std::dynamic_pointer_cast<tgui::Label>(_widget))
        w->getRenderer()->setTextStyle(style);
    else if (auto w = std::dynamic_pointer_cast<tgui::Button>(_widget))
        w->getRenderer()->setTextStyle(style);
}

/**
 * @brief Set the font of the widget.
 * @param fontPath Path to the font file
 */
void GuiWidget::setFont(const std::string& fontPath)
{
    _widget->getRenderer()->setFont(tgui::Font(fontPath));
}

/**
 * @brief Set the callback function for the widget (e.g., button press).
 * @param callback The callback function
 */
void GuiWidget::setCallback(std::function<void()> callback)
{
    _onClick = callback;
    if (auto w = std::dynamic_pointer_cast<tgui::Button>(_widget)) {
        w->onPress(callback);
    }
}

/**
 * @brief Set the placeholder text for EditBox widgets.
 * @param placeholder The placeholder text
 */
void GuiWidget::setPlaceholder(const std::string& placeholder)
{
    if (auto w = std::dynamic_pointer_cast<tgui::EditBox>(_widget))
        w->setDefaultText(placeholder);
}

/**
 * @biref set the password mode for EditBox widgets.
 * @param passwordMode True to enable password mode, false otherwise
 */
void GuiWidget::setPasswordMode(bool passwordMode)
{
    if (auto w = std::dynamic_pointer_cast<tgui::EditBox>(_widget))
        w->setPasswordCharacter('*');
}

/**
 * @brief Get the text of the widget.
 * @return The current text of the widget
 */
std::string GuiWidget::getText() const
{
    if (auto w = std::dynamic_pointer_cast<tgui::Label>(_widget)) return w->getText().toStdString();
    if (auto w = std::dynamic_pointer_cast<tgui::EditBox>(_widget)) return w->getText().toStdString();
    return "";
}

/**
 * @brief Get the Size of the widget.
 * @return The current size of the widget
 */
sf::Vector2f GuiWidget::getSize() const
{
    return {_widget->getSize().x, _widget->getSize().y};
}

/**
 * @brief Get the Position of the widget.
 * @return The current position of the widget
 */
sf::Vector2f GuiWidget::getPosition() const
{
    return {_widget->getPosition().x, _widget->getPosition().y};
}

/**
 * @brief Set the text alignment of the widget.
 * @param alignment The alignment to set (Left, Center, Right)
 */
void GuiWidget::setTextAlignment(tgui::HorizontalAlignment alignment)
{
    if (auto w = std::dynamic_pointer_cast<tgui::Label>(_widget))
        w->setHorizontalAlignment(alignment);
}

/**
 * @brief Set whether an EditBox is read-only.
 * @param readOnly True to make read-only, false otherwise
 */
void GuiWidget::setReadOnly(bool readOnly)
{
    if (auto w = std::dynamic_pointer_cast<tgui::EditBox>(_widget))
        w->setReadOnly(readOnly);
}

/**
 * @brief Set an input validator for EditBox widgets (e.g., regex for numbers).
 * @param regex The regex pattern string
 */
void GuiWidget::setInputValidator(const std::string& regex)
{
    if (auto w = std::dynamic_pointer_cast<tgui::EditBox>(_widget))
        w->setInputValidator(regex);
}

/**
 * @brief Set the value for a Slider widget.
 * @param value The value to set
 */
void GuiWidget::setValue(float value)
{
    if (auto w = std::dynamic_pointer_cast<tgui::Slider>(_widget))
        w->setValue(value);
}

/**
 * @brief Set the range for a Slider widget.
 * @param min Minimum value
 * @param max Maximum value
 */
void GuiWidget::setRange(float min, float max)
{
    if (auto w = std::dynamic_pointer_cast<tgui::Slider>(_widget)) {
        w->setMinimum(min);
        w->setMaximum(max);
    }
}

/**
 * @brief Set the checked state for a CheckBox widget.
 * @param checked True to check, false to uncheck
 */
void GuiWidget::setChecked(bool checked)
{
    if (auto w = std::dynamic_pointer_cast<tgui::CheckBox>(_widget))
        w->setChecked(checked);
}

/**
 * @brief Get the current value of a Slider widget.
 * @return The current value, or 0.0f if not a slider
 */
float GuiWidget::getValue() const
{
    if (auto w = std::dynamic_pointer_cast<tgui::Slider>(_widget))
        return w->getValue();
    return 0.0f;
}

/**
 * @brief Check if a CheckBox is currently checked.
 * @return True if checked, false otherwise
 */
bool GuiWidget::isChecked() const
{
    if (auto w = std::dynamic_pointer_cast<tgui::CheckBox>(_widget))
        return w->isChecked();
    return false;
}

/**
 * @brief Get the type of the widget.
 * @return The WidgetType enum value
 */
WidgetType GuiWidget::getType() const
{
    return _type;
}

/**
 * @brief Get the raw TGUI widget pointer.
 * @return The TGUI widget pointer
 */
tgui::Widget::Ptr GuiWidget::getRawWidget() const
{
    return _widget;
}

/**
 * @brief Get the parent entity ID of the widget.
 * @return The parent entity ID
 */
uint64_t GuiWidget::getParentId() const
{
    return _parentId;
}

/**
 * @brief Check if the widget is attached to the GUI.
 * @return True if attached, false otherwise
 */
bool GuiWidget::isAttached() const
{
    return _isAttached;
}

/**
 * @brief Set whether the widget is attached to the GUI.
 * @param attached True to mark as attached, false otherwise
 */
void GuiWidget::setAttached(bool attached)
{
    _isAttached = attached;
}

/**
 * @brief Add space in a VerticalLayout widget.
 * @param ratio The ratio of space to add
 */
void GuiWidget::addSpace(float ratio)
{
    if (auto layout = std::dynamic_pointer_cast<tgui::VerticalLayout>(_widget))
        layout->addSpace(ratio);
}

/**
 * @brief Check if the widget is visible.
 * @return True if visible, false otherwise
 */
bool GuiWidget::isVisible() const
{
    return _isVisible;
}