#pragma once

#include "include/global.h"

#include <string>
#include <functional>
#include <vector>
#include <memory>

class Component {
    public:
        Component(const std::string& title, const Size& size, const Position& position, const Type& type=NONE);
        virtual ~Component() = default;
        void addComponent(Component* component);
        Handle getHandle() const;
        Handle getParent() const;
        Position getPosition() const;
        Size getSize() const;
        Type getType() const;
        std::vector<Component*> getComponents() const;

    protected:
        std::string title;
        Handle handle;
        Handle parent;
        Position position;
        Size size;
        std::vector<Component*> components;
        Type type;
};
