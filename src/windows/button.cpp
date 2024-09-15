#include "button.h"
#include "include/global.h"
#include <memory>

#pragma region WinButton
WinButton::WinButton(const std::string& title, const Position& position, const Component& parent, const std::function<void()>& callback) 
: Button(title, position, Size(STD_BTN_SIZE_WIDTH, STD_BTN_SIZE_HEIGHT)) {
    this->parent = parent.getHandle();
    this->callback = callback;

    std::wstring wstr(this->title.begin(), this->title.end());

    handle = reinterpret_cast<Handle>(CreateWindowW( 
        L"BUTTON",
        wstr.c_str(),
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

Button* createButton(const std::string& title, const Position& position, std::shared_ptr<Component> parent, const std::function<void()>& callback) {
    parent->addComponent(WinButton(title, position, *parent, callback));
    return reinterpret_cast<Button*>(&(parent->getComponents().back()));
}
#pragma endregion Button
