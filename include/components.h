#pragma once

#include "component.h"

class Window : public Component {
    public:
        Window(const std::string& title, const Position& position, const Size& size) : Component(title, position, size) {}
        virtual ~Window() = default;
};

class Button : public Component {
    public:
        Button(const std::string& title, const Position& position, const Size& size) : Component(title, position, size, BUTTON) {}
        virtual ~Button() = default;
        virtual void onClick() = 0;

    protected:
        std::function<void()> callback;
};
Button* createButton(const std::string& title, const Position& position, std::shared_ptr<Component> parent, const std::function<void()>& callback);
