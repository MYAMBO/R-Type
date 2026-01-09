/*
** EPITECH PROJECT, 2026
** R-Type
** File description:
** GuiWidget
*/

#ifndef GUIWIDGET_HPP_
    #define GUIWIDGET_HPP_

    #include <TGUI/TGUI.hpp>
    #include <string>
    #include <functional>
    #include "Component.hpp"

enum class WidgetType {
    LABEL,
    BUTTON,
    PANEL,
    VERTICAL_LAYOUT,
    HORIZONTAL_LAYOUT,
    EDIT_BOX,
    PICTURE,
    SCROLLABLE_PANEL,
    CHECKBOX,
    SLIDER
};

/**
 * @brief Component representing a GUI widget using TGUI.
*/
class GuiWidget : public Component {
    public:
        GuiWidget(WidgetType type, const std::string& content = "", uint64_t parentId = 0);
        ~GuiWidget() override = default;

        void setSize(float w, float h);
        void setSize(const std::string& w, const std::string& h);
        void setPosition(float x, float y);
        void setPosition(const std::string& x, const std::string& y);
        void setVisible(bool visible);
        void setEnabled(bool enabled);
        void setOrigin(float x, float y);
        void setFocus();
        void setScale(float x, float y);
        
        void setFont(const std::string& fontPath);
        void setText(const std::string& text);
        void setTextSize(unsigned int size);
        void setTextColor(sf::Color color);
        void setTextStyle(tgui::TextStyle style);
        void setTextAlignment(tgui::HorizontalAlignment alignment);

        void setCallback(std::function<void()> callback);
        std::function<void()> getCallback() const { return _onClick; }

        void setPlaceholder(const std::string& placeholder);
        void setReadOnly(bool readOnly);
        void setPasswordMode(bool passwordMode);
        void setInputValidator(const std::string& regex);

        void setValue(float value);
        void setRange(float min, float max);
        void setChecked(bool checked);
        void setAutoSize(bool autoSize);

        [[nodiscard]] std::string getText() const;
        [[nodiscard]] float getValue() const;
        [[nodiscard]] bool isChecked() const;
        [[nodiscard]] sf::Vector2f getSize() const;
        [[nodiscard]] sf::Vector2f getScale() const;
        [[nodiscard]] float getTextSize() const;
        [[nodiscard]] sf::Vector2f getPosition() const;
        [[nodiscard]] WidgetType getType() const;

        tgui::Widget::Ptr getRawWidget() const;
        uint64_t getParentId() const;
        bool isAttached() const;
        void setAttached(bool attached);

    private:
        tgui::Widget::Ptr _widget;
        WidgetType _type;
        uint64_t _parentId;
        bool _isAttached = false;
        std::function<void()> _onClick;
    };

#endif