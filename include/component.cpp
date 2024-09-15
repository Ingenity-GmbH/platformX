#pragma once

#include "component.h"

Component::Component(const std::string& title,  const Size& size, const Position& position, const Type& type)
: title(title), size(size), position(position), type(type), handle(NULL), parent(NULL) {}

void Component::addComponent(Component* component) {
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

std::vector<Component*> Component::getComponents() const {
    return components;
}
