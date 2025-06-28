#include "../include/control.h"
#include "../include/util.h"

#pragma region PXControl
PXControl::PXControl(const std::string& title, const PXPosition& position, const PXSize& size, const PXType& type)
: title(title), position(position), size(size), type(type), handle(0), parent(0) {}

PXControl::~PXControl() {
    for (PXControl* control : controls) {
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

PXHandle PXControl::getParent() const {
    return parent;
}

PXPosition PXControl::getPosition() const {
    return position;
}

PXSize PXControl::getSize() const {
    return size;
}

PXType PXControl::getType() const {
    return type;
}

void PXControl::setTitle(const std::string& title) {
    this->title = title;
    util::setTitle(handle, title);
}

std::string PXControl::getTitle() {
    title = util::getTitle(handle);
    return title;
}

std::vector<PXControl*> PXControl::getControls() const {
    return controls;
}

std::shared_ptr<PXControl> PXControl::getSharedPtr() {
    return shared_from_this();
}
#pragma endregion PXControl
