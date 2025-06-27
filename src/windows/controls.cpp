#include "include/global.h"
#include "include/util.h"
#include "controls.h"

#include <string>
#include <CommCtrl.h>

#pragma region WinButton
WinButton::WinButton(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) 
: PXButton(title, position, size) {
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
    
    util::setFont(handle);
}

void WinButton::onClick() {
    callback();
}

PXButton* createButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) {
    parent->addControl(new WinButton(title, *parent, position, size, callback));
    return static_cast<PXButton*>(parent->getControls().back());
}
PXButton* createButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback) {
    return createButton(title,  parent,  position, {STD_BTN_SIZE_WIDTH,STD_BTN_SIZE_HEIGHT}, callback);
}
#pragma endregion WinButton

#pragma region WinEdit
WinEdit::WinEdit(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXEdit(title, position, size) {
    this->parent = parent.getHandle();
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "EDIT",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        position.x,
        position.y,
        size.width,
        size.height,
        this->parent,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(this->parent, GWLP_HINSTANCE), 
        nullptr));

        util::setFont(handle);
}

void WinEdit::onKeyPress(const uint32_t& key) {
    callback(key);
}

PXEdit* createEdit(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    parent->addControl(new WinEdit(title, *parent, position, size, callback));
    return static_cast<PXEdit*>(parent->getControls().back());
}
PXEdit* createEdit(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createEdit(title, parent, position, {STD_EDIT_SIZE_WIDTH,STD_EDIT_SIZE_HEIGHT}, callback);
}
#pragma endregion WinEdit

#pragma region WinText
WinText::WinText(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXText(title, position, size) {
    this->parent = parent.getHandle();
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "STATIC",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | SS_LEFT | TRANSPARENT,
        position.x,
        position.y,
        size.width,
        size.height,
        this->parent,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(this->parent, GWLP_HINSTANCE), 
        nullptr));

    util::setFont(handle);
}

// void WinText::onKeyPress(const uint32_t& key) {
//     callback(key);
// }

PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    parent->addControl(new WinText(title, *parent, position, size, callback));
    return static_cast<PXText*>(parent->getControls().back());
}
PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createText(title, parent, position, {STD_TEXT_SIZE_WIDTH,STD_TEXT_SIZE_HEIGHT}, callback);
}
#pragma endregion WinText

#pragma region WinListBox
WinListBox::WinListBox(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXListBox(title, position, size) {
    this->parent = parent.getHandle();
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA(
        "LISTBOX",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY,
        position.x,
        position.y,
        size.width,
        size.height,
        this->parent,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(this->parent, GWLP_HINSTANCE), 
        nullptr));

    util::setFont(handle);
}

// void WinListBox::onKeyPress(const uint32_t& key) {
//     callback(key);
// }

void WinListBox::addItem(const std::string& title, const size_t& pos) {
    if (pos < items.size())
        items.insert(items.begin() + pos, title);
    else
        items.push_back(title);
    util::addItems(handle, items);
}
        
void WinListBox::removeItem(const size_t& pos) {
    if (pos < items.size()) {
        items.erase(items.begin() + pos);
        util::addItems(handle, items);
    }
}

size_t WinListBox::getSelectedItem() const {
   return util::getSelectedItem(handle, this->getType());
}

PXListBox* createListBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    parent->addControl(new WinListBox(title, *parent, position, size, callback));
    return static_cast<PXListBox*>(parent->getControls().back());
}
PXListBox* createListBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createListBox(title, parent, position, {STD_LISTBOX_SIZE_WIDTH,STD_LISTBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinListBox

#pragma region WinComboBox
WinComboBox::WinComboBox(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXComboBox(title, position, size) {
    this->parent = parent.getHandle();
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA(
        "COMBOBOX",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY,
        position.x,
        position.y,
        size.width,
        size.height,
        this->parent,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(this->parent, GWLP_HINSTANCE), 
        nullptr));

    util::setFont(handle);
}

// void WinComboBox::onKeyPress(const uint32_t& key) {
//     callback(key);
// }

void WinComboBox::addItem(const std::string& title, const size_t& pos) {
    if (pos < items.size())
        items.insert(items.begin() + pos, title);
    else
        items.push_back(title);
    util::addItems(handle, items);
}
        
void WinComboBox::removeItem(const size_t& pos) {
    if (pos < items.size()) {
        items.erase(items.begin() + pos);
        util::addItems(handle, items);
    }
}

size_t WinComboBox::getSelectedItem() const {
    return util::getSelectedItem(handle, this->getType());
}

PXComboBox* createComboBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    parent->addControl(new WinComboBox(title, *parent, position, size, callback));
    return static_cast<PXComboBox*>(parent->getControls().back());
}
PXComboBox* createComboBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createComboBox(title, parent, position, {STD_COMBOBOX_SIZE_WIDTH,STD_COMBOBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinComboBox

#pragma region WinProgressBar
WinProgressBar::WinProgressBar(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXProgressBar(title, position, size) {
    this->parent = parent.getHandle();
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "msctls_progress32",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE,
        position.x,
        position.y,
        size.width,
        size.height,
        this->parent,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(this->parent, GWLP_HINSTANCE), 
        nullptr));

    util::setFont(handle);

    SetWindowLong(static_cast<HWND>(handle), GWL_STYLE, GetWindowLong(static_cast<HWND>(handle), GWL_STYLE) | PBS_MARQUEE);
    SendMessage(static_cast<HWND>(handle), PBM_SETMARQUEE, (WPARAM)TRUE, (LPARAM)30);
}

// void WinProgressBar::onKeyPress(const uint32_t& key) {
//	 callback(key);
// }

void WinProgressBar::configure(const uint32_t& min, const uint32_t& max, const uint32_t& step) {
    SendMessage(static_cast<HWND>(handle), PBM_SETRANGE, 0, MAKELPARAM(min, max));
    SendMessage(static_cast<HWND>(handle), PBM_SETSTEP, (WPARAM)(step), 0);
}

void WinProgressBar::incStep() {
    SendMessage(static_cast<HWND>(handle), PBM_STEPIT, 0, 0);
}

void WinProgressBar::setPos(const uint32_t& pos) {
    SendMessage(static_cast<HWND>(handle), PBM_SETPOS, (WPARAM)(pos), 0);
}

void WinProgressBar::setColor(const PXColor& front, const PXColor& back) {
    SendMessage(static_cast<HWND>(handle), PBM_SETBARCOLOR, 0, (LPARAM)RGB(front.r, front.g, front.b));
    SendMessage(static_cast<HWND>(handle), PBM_SETBKCOLOR, 0, (LPARAM)RGB(back.r, back.g, back.b));
}

PXProgressBar* createProgressBar(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    parent->addControl(new WinProgressBar(title, *parent, position, size, callback));
    return static_cast<PXProgressBar*>(parent->getControls().back());
}
PXProgressBar* createProgressBar(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createProgressBar(title, parent, position, {STD_PROGRESSBAR_SIZE_WIDTH,STD_PROGRESSBAR_SIZE_HEIGHT}, callback);
}
#pragma endregion WinProgressBar
