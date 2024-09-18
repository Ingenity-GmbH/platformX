#include "components.h"

#pragma region PXComponent
PXComponent::PXComponent(const std::string& title,  const PXSize& size, const PXPosition& position, const PXType& type)
: title(title), size(size), position(position), type(type), handle(0), parent(0) {}

void PXComponent::addComponent(PXComponent* component) {
    components.push_back(component);
}

PXHandle PXComponent::getHandle() const {
    return handle;
}

PXHandle PXComponent::getParent() const {
    return parent;
}

PXPosition PXComponent::getPosition() const {
    return position;
}

PXSize PXComponent::getSize() const {
    return size;
}

PXType PXComponent::getType() const {
    return type;
}

std::vector<PXComponent*> PXComponent::getComponents() const {
    return components;
}
#pragma endregion PXComponent
