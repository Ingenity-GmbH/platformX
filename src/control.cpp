#include "../include/control.h"
#include "../include/util.h"

#pragma region PXControl
PXControl::PXControl(const PXString& title, const PXPosition& position, const PXSize& size, const PXType& type)
: title(title), position(position), size(size), type(type), handle(0), parent(0) {}

PXControl::~PXControl() {
    for (auto& control : controls) {
        if (control) {
            delete control;
            control = nullptr;
        }
    }
}

void PXControl::addControl(PXControl* control) {
    controls.push_back(control);
}

PXHandle PXControl::getHandle() const {
    return handle;
}

PXControl* PXControl::getParent() {
    return parent;
}

void PXControl::setPosition(const PXPosition& position) {
    this->position = position;
}

PXPosition PXControl::getPosition() {
    return position;
}

void PXControl::setSize(const PXSize& size) {
    this->size = size;
}

PXSize PXControl::getSize() {
    return size;
}

PXType PXControl::getType() const {
    return type;
}

void PXControl::setTitle(const PXString& title) {
    this->title = title;
    util::setTitle(handle, title);
}

PXString PXControl::getTitle() {
    title = util::getTitle(handle);
    return title;
}

std::vector<PXControl*> PXControl::getControls() const {
    return controls;
}
#pragma endregion PXControl
