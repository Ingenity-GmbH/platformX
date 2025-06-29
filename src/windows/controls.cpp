#include "include/global.h"
#include "include/util.h"
#include "controls.h"

#include <string>
#include <CommCtrl.h>

#pragma region WinButton
WinButton::WinButton(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) 
: PXButton(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "BUTTON",
        this->title.c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr));
    
    util::setFont(handle);
}

void WinButton::onClick() {
    callback();
}

PXButton* createButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinButton(title, *newParent, newPosition, size, callback));
    return static_cast<PXButton*>(newParent->getControls().back());
}
PXButton* createButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback) {
    return createButton(title,  parent,  position, {STD_BTN_SIZE_WIDTH,STD_BTN_SIZE_HEIGHT}, callback);
}
#pragma endregion WinButton

#pragma region WinEdit
WinEdit::WinEdit(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXEdit(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "EDIT",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr));

        util::setFont(handle);
}

void WinEdit::onKeyPress(const uint32_t& key) {
    callback(key);
}

PXEdit* createEdit(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinEdit(title, *newParent, newPosition, size, callback));
    return static_cast<PXEdit*>(newParent->getControls().back());
}
PXEdit* createEdit(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createEdit(title, parent, position, {STD_EDIT_SIZE_WIDTH,STD_EDIT_SIZE_HEIGHT}, callback);
}
#pragma endregion WinEdit

#pragma region WinText
WinText::WinText(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXText(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "STATIC",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | SS_LEFT | TRANSPARENT,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr));

    util::setFont(handle);
}

// void WinText::onKeyPress(const uint32_t& key) {
//     callback(key);
// }

PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinText(title, *newParent, newPosition, size, callback));
    return static_cast<PXText*>(newParent->getControls().back());
}
PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createText(title, parent, position, {STD_TEXT_SIZE_WIDTH,STD_TEXT_SIZE_HEIGHT}, callback);
}
#pragma endregion WinText

#pragma region WinListBox
WinListBox::WinListBox(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXListBox(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA(
        "LISTBOX",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
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
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinListBox(title, *newParent, newPosition, size, callback));
    return static_cast<PXListBox*>(newParent->getControls().back());
}
PXListBox* createListBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createListBox(title, parent, position, {STD_LISTBOX_SIZE_WIDTH,STD_LISTBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinListBox

#pragma region WinComboBox
WinComboBox::WinComboBox(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXComboBox(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA(
        "COMBOBOX",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
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
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinComboBox(title, *newParent, newPosition, size, callback));
    return static_cast<PXComboBox*>(newParent->getControls().back());
}
PXComboBox* createComboBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createComboBox(title, parent, position, {STD_COMBOBOX_SIZE_WIDTH,STD_COMBOBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinComboBox

#pragma region WinProgressBar
WinProgressBar::WinProgressBar(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXProgressBar(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "msctls_progress32",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
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
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinProgressBar(title, *newParent, newPosition, size, callback));
    return static_cast<PXProgressBar*>(newParent->getControls().back());
}
PXProgressBar* createProgressBar(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createProgressBar(title, parent, position, {STD_PROGRESSBAR_SIZE_WIDTH,STD_PROGRESSBAR_SIZE_HEIGHT}, callback);
}
#pragma endregion WinProgressBar

#pragma region WinCheckBox
WinCheckBox::WinCheckBox(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback) 
: PXCheckBox(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;    
    if (callback)
        this->callback = callback;
    else
        this->callback = util::toggleState;

    handle = reinterpret_cast<PXHandle>(CreateWindowA( 
        "BUTTON",
        this->title.c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr));

    util::setFont(handle);
}

void WinCheckBox::onClick() {
    callback(handle);
}

void WinCheckBox::setState(const bool& state) {
    util::setState(handle, state);
}

bool WinCheckBox::getState() const {
    return util::getState(handle);
}

void WinCheckBox::toggleState() {
    util::toggleState(handle);
}

PXCheckBox* createCheckBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinCheckBox(title, *newParent, newPosition, size, callback));
    return static_cast<PXCheckBox*>(newParent->getControls().back());
}
PXCheckBox* createCheckBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const PXHandle& handle)>& callback) {
    return createCheckBox(title, parent, position, {STD_CHECKBOX_SIZE_WIDTH,STD_CHECKBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinText

#pragma region WinRadioButton
WinRadioButton::WinRadioButton(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback) 
: PXRadioButton(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    if (callback)
        this->callback = callback;
    else
        this->callback = util::toggleState;

    handle = static_cast<PXHandle>(CreateWindowA( 
        "BUTTON",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr));

    util::setFont(handle);
}

void WinRadioButton::onClick() {
	 callback(handle);
}

void WinRadioButton::setState(const bool& state) {
    util::setState(handle, state);
}

bool WinRadioButton::getState() const {
    return util::getState(handle);
}

void WinRadioButton::toggleState() {
    util::toggleState(handle);
}

PXRadioButton* createRadioButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinRadioButton(title, *newParent, newPosition, size, callback));
    return static_cast<PXRadioButton*>(newParent->getControls().back());
}
PXRadioButton* createRadioButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const PXHandle& handle)>& callback) {
    return createRadioButton(title, parent, position, {STD_RADIOBUTTON_SIZE_WIDTH,STD_RADIOBUTTON_SIZE_HEIGHT}, callback);
}
#pragma endregion WinRadioButton

#pragma region WinGroupBox
WinGroupBox::WinGroupBox(const std::string& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) 
: PXGroupBox(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = static_cast<PXHandle>(CreateWindowA(
        "BUTTON",
        this->title.c_str(),
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr));

    util::setFont(handle);
}

PXGroupBox* createGroupBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinGroupBox(title, *newParent, newPosition, size, callback));
    return static_cast<PXGroupBox*>(newParent->getControls().back());
}
PXGroupBox* createGroupBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback) {
    return createGroupBox(title, parent, position, {STD_GROUPBOX_SIZE_WIDTH,STD_GROUPBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinGroupBox
