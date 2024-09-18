#include "button.h"
#include "include/global.h"
#include <memory>

#pragma region WinButton
WinButton::WinButton(const std::string& title, const PXPosition& position, const PXComponent& parent, const std::function<void()>& callback) 
: PXButton(title, PXSize(STD_BTN_SIZE_WIDTH, STD_BTN_SIZE_HEIGHT), position) {
    this->parent = parent.getHandle();
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "BUTTON",
        this->title.c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        position.x,
        position.y,
        size.width,
        size.height,
        this->parent,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(this->parent, GWLP_HINSTANCE), 
        nullptr));
}

void WinButton::onClick() {
    callback();
}

PXButton* createButton(const std::string& title, const PXPosition& position, std::shared_ptr<PXComponent> parent, const std::function<void()>& callback) {
    parent->addComponent(new WinButton(title, position, *parent, callback));
    return static_cast<PXButton*>(parent->getComponents().back());
}
#pragma endregion WinButton
