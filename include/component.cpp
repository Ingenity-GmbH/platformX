#pragma once

#include "component.h"

Component::Component(const std::string& title, const Position& position, const Size& size, const Type& type)
: title(title), position(position), size(size), type(type), handle(NULL), parent(NULL) {}

void Component::addComponent(const Component& component) {
    components.push_back(component);
}

Handle Component::getHandle() const {
    return handle;
}

Handle Component::getParent() const {
    return parent;
}

Position Component::getPosition() const {
    return position;
}

Size Component::getSize() const {
    return size;
}

Type Component::getType() const {
    return type;
}

std::vector<Component> Component::getComponents() const {
    return components;
}
