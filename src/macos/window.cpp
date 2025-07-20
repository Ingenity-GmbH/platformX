
#include "include/global.h"
#include "include/util.h"
// #include "controls.h"
#include "window.h"

#pragma region MacOSWindow
void MacOSWindow::setSize(const PXSize& size) {
    PXControl::setSize(size);
    setPosition(position);
}

void MacOSWindow::setPosition(const PXPosition& position) {
    PXControl::setPosition(position);
    util::setSizePosition(handle, getSize(), position);
}

PXPosition MacOSWindow::getPosition() {
    return PXControl::getPosition();
}

PXSize MacOSWindow::getSize() {
    return PXControl::getSize();
}
#pragma endregion MacOSWindow

#pragma region MacOSMainWindow
MacOSMainWindow::MacOSMainWindow(const PXString& title) : MacOSWindow(title, false) {}

PXWindowSharedPtr createMainWindow(const PXString& title) {
    return PXWindowSharedPtr(new MacOSMainWindow(title));
}
#pragma endregion MacOSMainWindow

#pragma region MacOSChildWindow
MacOSChildWindow::MacOSChildWindow(const PXString& title, PXControlSharedPtr& parent, const PXPosition& position, const PXSize& size) : MacOSWindow(title, true, parent) {
    setPosition(position);
    setSize(size);
}

PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size) {
    parent->addControl(new MacOSChildWindow(title, parent, position, size));
    return PXWindowSharedPtr(reinterpret_cast<PXWindow*>(parent->getControls().back()));
}

PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXPosition& position) {
    return createWindow(title, parent, position, PXSize(STD_CHILDWIN_SIZE_WIDTH, STD_CHILDWIN_SIZE_HEIGHT));
}

PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXSize& size) {
    return createWindow(title, parent, PXPosition(parent->getPosition().x+(parent->getSize().width-size.height)/2,parent->getPosition().y+(parent->getSize().height-size.height)/2), size);
}

PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent) {
    return createWindow(title, parent, PXPosition(parent->getPosition().x+(parent->getSize().width-STD_CHILDWIN_SIZE_WIDTH)/2,parent->getPosition().y+(parent->getSize().height-STD_CHILDWIN_SIZE_HEIGHT)/2), PXSize(STD_CHILDWIN_SIZE_WIDTH, STD_CHILDWIN_SIZE_HEIGHT));
}
#pragma endregion MacOSChildWindow
