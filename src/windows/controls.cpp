#include "include/global.h"
#include "include/util.h"
#include "controls.h"

#pragma region WinButton
WinButton::WinButton(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) 
: PXButton(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = CreateWindowEx( 
        0,
        L"BUTTON",
        this->title.toLPCWSTR(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);
    
    util::setFont(handle);
}

void WinButton::onClick() {
    callback();
}

PXButton* createButton(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinButton(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXButton*>(newParent->getControls().back());
}
PXButton* createButton(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback) {
    return createButton(title,  parent,  position, {STD_BTN_SIZE_WIDTH,STD_BTN_SIZE_HEIGHT}, callback);
}
#pragma endregion WinButton

#pragma region WinEdit
WinEdit::WinEdit(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXEdit(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = CreateWindowEx( 
        0,
        L"EDIT",
        this->title.toLPCWSTR(),
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);

        util::setFont(handle);
}

void WinEdit::onKeyPress(const uint32_t& key) {
    callback(key);
}

PXEdit* createEdit(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinEdit(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXEdit*>(newParent->getControls().back());
}
PXEdit* createEdit(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createEdit(title, parent, position, {STD_EDIT_SIZE_WIDTH,STD_EDIT_SIZE_HEIGHT}, callback);
}
#pragma endregion WinEdit

#pragma region WinText
WinText::WinText(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXText(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = CreateWindowEx( 
        0,
        L"STATIC",
        this->title.toLPCWSTR(),
        WS_CHILD | WS_VISIBLE | SS_LEFT | TRANSPARENT,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);

    util::setFont(handle);
}

// void WinText::onKeyPress(const uint32_t& key) {
//     callback(key);
// }

PXText* createText(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinText(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXText*>(newParent->getControls().back());
}
PXText* createText(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createText(title, parent, position, {STD_TEXT_SIZE_WIDTH,STD_TEXT_SIZE_HEIGHT}, callback);
}
#pragma endregion WinText

#pragma region WinListBox
WinListBox::WinListBox(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXListBox(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = CreateWindowEx(
        0,
        L"LISTBOX",
        this->title.toLPCWSTR(),
        WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);

    util::setFont(handle);
}

// void WinListBox::onKeyPress(const uint32_t& key) {
//     callback(key);
// }

void WinListBox::addNode(PXNode& node, const size_t& pos) {
    if (pos < nodes.size())
        nodes.insert(nodes.begin() + pos, node);
    else
        nodes.push_back(node);
    util::addNodes(handle, nodes, type);
}
        
void WinListBox::removeNode(const size_t& pos) {
    if (pos < nodes.size()) {
        nodes.erase(nodes.begin() + pos);
        util::addNodes(handle, nodes, type);
    }
}

const PXNode* WinListBox::getSelectedNode() const {
   return &(nodes.at(util::getSelectedNode(handle, type)));
}

PXListBox* createListBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinListBox(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXListBox*>(newParent->getControls().back());
}
PXListBox* createListBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createListBox(title, parent, position, {STD_LISTBOX_SIZE_WIDTH,STD_LISTBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinListBox

#pragma region WinComboBox
WinComboBox::WinComboBox(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXComboBox(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = CreateWindowEx(
        0,
        L"COMBOBOX",
        this->title.toLPCWSTR(),
        WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);

    util::setFont(handle);
}

// void WinComboBox::onKeyPress(const uint32_t& key) {
//     callback(key);
// }

void WinComboBox::addNode(PXNode& node, const size_t& pos) {
    if (pos < nodes.size())
        nodes.insert(nodes.begin() + pos, node);
    else
        nodes.push_back(node);
    util::addNodes(handle, nodes, type);
}
        
void WinComboBox::removeNode(const size_t& pos) {
    if (pos < nodes.size()) {
        nodes.erase(nodes.begin() + pos);
        util::addNodes(handle, nodes, type);
    }
}

const PXNode* WinComboBox::getSelectedNode() const {
    return &nodes.at(util::getSelectedNode(handle, type));
}

PXComboBox* createComboBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinComboBox(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXComboBox*>(newParent->getControls().back());
}
PXComboBox* createComboBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createComboBox(title, parent, position, {STD_COMBOBOX_SIZE_WIDTH,STD_COMBOBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinComboBox

#pragma region WinProgressBar
WinProgressBar::WinProgressBar(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) 
: PXProgressBar(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = CreateWindowEx( 
        0,
        L"msctls_progress32",
        this->title.toLPCWSTR(),
        WS_CHILD | WS_VISIBLE,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);

    util::setFont(handle);

    SetWindowLong(handle, GWL_STYLE, GetWindowLong(handle, GWL_STYLE) | PBS_MARQUEE);
    SendMessage(handle, PBM_SETMARQUEE, (WPARAM)TRUE, (LPARAM)30);
}

// void WinProgressBar::onKeyPress(const uint32_t& key) {
//	 callback(key);
// }

void WinProgressBar::configure(const uint32_t& min, const uint32_t& max, const uint32_t& step) {
    SendMessage(handle, PBM_SETRANGE, 0, MAKELPARAM(min, max));
    SendMessage(handle, PBM_SETSTEP, (WPARAM)(step), 0);
}

void WinProgressBar::incStep() {
    SendMessage(handle, PBM_STEPIT, 0, 0);
}

void WinProgressBar::setPos(const uint32_t& pos) {
    SendMessage(handle, PBM_SETPOS, (WPARAM)(pos), 0);
}

void WinProgressBar::setColor(const PXColor& front, const PXColor& back) {
    SendMessage(handle, PBM_SETBARCOLOR, 0, (LPARAM)RGB(front.r, front.g, front.b));
    SendMessage(handle, PBM_SETBKCOLOR, 0, (LPARAM)RGB(back.r, back.g, back.b));
}

PXProgressBar* createProgressBar(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinProgressBar(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXProgressBar*>(newParent->getControls().back());
}
PXProgressBar* createProgressBar(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createProgressBar(title, parent, position, {STD_PROGRESSBAR_SIZE_WIDTH,STD_PROGRESSBAR_SIZE_HEIGHT}, callback);
}
#pragma endregion WinProgressBar

#pragma region WinCheckBox
WinCheckBox::WinCheckBox(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback) 
: PXCheckBox(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;    
    if (callback)
        this->callback = callback;
    else
        this->callback = util::toggleState;

    handle = CreateWindowEx( 
        0,
        L"BUTTON",
        this->title.toLPCWSTR(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);

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

PXCheckBox* createCheckBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinCheckBox(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXCheckBox*>(newParent->getControls().back());
}
PXCheckBox* createCheckBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const PXHandle& handle)>& callback) {
    return createCheckBox(title, parent, position, {STD_CHECKBOX_SIZE_WIDTH,STD_CHECKBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinText

#pragma region WinRadioButton
WinRadioButton::WinRadioButton(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback) 
: PXRadioButton(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    if (callback)
        this->callback = callback;
    else
        this->callback = util::toggleState;

    handle = CreateWindowEx( 
        0,
        L"BUTTON",
        this->title.toLPCWSTR(),
        WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);

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

PXRadioButton* createRadioButton(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinRadioButton(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXRadioButton*>(newParent->getControls().back());
}
PXRadioButton* createRadioButton(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const PXHandle& handle)>& callback) {
    return createRadioButton(title, parent, position, {STD_RADIOBUTTON_SIZE_WIDTH,STD_RADIOBUTTON_SIZE_HEIGHT}, callback);
}
#pragma endregion WinRadioButton

#pragma region WinGroupBox
WinGroupBox::WinGroupBox(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) 
: PXGroupBox(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = CreateWindowEx(
        0,
        L"BUTTON",
        this->title.toLPCWSTR(),
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE), 
        nullptr);

    util::setFont(handle);
}

PXGroupBox* createGroupBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;
    
    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    } 
    newParent->addControl(new WinGroupBox(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXGroupBox*>(newParent->getControls().back());
}
PXGroupBox* createGroupBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback) {
    return createGroupBox(title, parent, position, {STD_GROUPBOX_SIZE_WIDTH,STD_GROUPBOX_SIZE_HEIGHT}, callback);
}
#pragma endregion WinGroupBox

#pragma region WinTreeView
WinTreeView::WinTreeView(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) 
: PXTreeView(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    handle = CreateWindowEx(
        0,
        WC_TREEVIEW,
        this->title.toLPCWSTR(),
        WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES,
        position.x,
        position.y,
        size.width,
        size.height,
        parentHandle,
        nullptr,
        (HINSTANCE)GetWindowLongPtr(parentHandle, GWLP_HINSTANCE),
        nullptr);

    util::setFont(handle);
}

void WinTreeView::onClick() {
	 callback();
}
// void WinTreeView::onKeyPress(const uint32_t& key) {
//	 callback(key);
// }

void WinTreeView::addNode(PXNode& node, const size_t& pos) {
    if (pos < nodes.size())
        nodes.insert(nodes.begin() + pos, node);
    else
        nodes.push_back(node);
    util::addNodes(handle, nodes, type);
}
        
void WinTreeView::removeNode(const size_t& pos) {
    if (pos < nodes.size()) {
        nodes.erase(nodes.begin() + pos);
        util::addNodes(handle, nodes, type);
    }
}

const PXNode* WinTreeView::getSelectedNode() const {
    auto nodeHandle = reinterpret_cast<HTREEITEM>(util::getSelectedNode(handle, type));
    for (const auto& node : nodes) {
        if (node.handle == nodeHandle)
            return &node;
    }
    return nullptr;
}

PXTreeView* createTreeView(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback) {
    PXControl* newParent = parent.get();
    PXPosition newPosition = position;

    while (newParent->getType() != WINDOW) {
        newPosition += newParent->getPosition();
        newParent = newParent->getParent();
    }
    newParent->addControl(new WinTreeView(title, *newParent, newPosition, size, callback));
    return reinterpret_cast<PXTreeView*>(newParent->getControls().back());
}
PXTreeView* createTreeView(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback) {
    return createTreeView(title, parent, position, {STD_TREEVIEW_SIZE_WIDTH,STD_TREEVIEW_SIZE_HEIGHT}, callback);
}
#pragma endregion WinTreeView
