#include "include/global.h"
#include "controls.h"

#include <string>

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

    HFONT hFont = CreateFontA(
        18,                        // Height
        0,                         // Width
        0,                         // Escapement
        0,                         // Orientation
        FW_NORMAL,                 // Weight
        FALSE,                     // Italic
        FALSE,                     // Underline
        0,                         // StrikeOut
        ANSI_CHARSET,              // CharSet
        OUT_DEFAULT_PRECIS,        // OutPrecision
        CLIP_DEFAULT_PRECIS,       // ClipPrecision
        DEFAULT_QUALITY,           // Quality
        DEFAULT_PITCH | FF_SWISS,  // PitchAndFamily
        WIN_STANDARD_FONT          // Facename
    );
    SendMessage(static_cast<HWND>(handle), WM_SETFONT, (WPARAM)hFont, TRUE);
}

void WinButton::onClick() {
    callback();
}

void WinButton::setTitle(const std::string& title) {
    this->title = title;
    SendMessage(static_cast<HWND>(handle), WM_SETTEXT, 0, (LPARAM)(&this->title));
}

std::string WinButton::getTitle() {
    int txtLen = SendMessage(static_cast<HWND>(handle), WM_GETTEXTLENGTH, 0, 0);
    std::unique_ptr<char> buffer(new char[txtLen+1]);
    SendMessage(static_cast<HWND>(handle), WM_GETTEXT, (WPARAM)(txtLen+1), (LPARAM)buffer.get());

    if (!buffer)
        this->title = "";
    this->title = std::string(buffer.get());

    return this->title;
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

        HFONT hFont = CreateFontA(
        18,                        // Height
        0,                         // Width
        0,                         // Escapement
        0,                         // Orientation
        FW_NORMAL,                 // Weight
        FALSE,                     // Italic
        FALSE,                     // Underline
        0,                         // StrikeOut
        ANSI_CHARSET,              // CharSet
        OUT_DEFAULT_PRECIS,        // OutPrecision
        CLIP_DEFAULT_PRECIS,       // ClipPrecision
        DEFAULT_QUALITY,           // Quality
        DEFAULT_PITCH | FF_SWISS,  // PitchAndFamily
        WIN_STANDARD_FONT          // Facename
    );
    SendMessage(static_cast<HWND>(handle), WM_SETFONT, (WPARAM)hFont, TRUE);
}

void WinEdit::onKeyPress(const uint32_t& key) {
    callback(key);
}

void WinEdit::setTitle(const std::string& title) {
    this->title = title;
    SendMessage(static_cast<HWND>(handle), WM_SETTEXT, 0, (LPARAM)(&this->title));
}

std::string WinEdit::getTitle() {
    int txtLen = SendMessage(static_cast<HWND>(handle), WM_GETTEXTLENGTH, 0, 0);
    std::unique_ptr<char> buffer(new char[txtLen+1]);
    SendMessage(static_cast<HWND>(handle), WM_GETTEXT, (WPARAM)(txtLen+1), (LPARAM)buffer.get());

    if (!buffer)
        this->title = "";
    this->title = std::string(buffer.get());

    return this->title;
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

    HFONT hFont = CreateFontA(
        18,                        // Height
        0,                         // Width
        0,                         // Escapement
        0,                         // Orientation
        FW_NORMAL,                 // Weight
        FALSE,                     // Italic
        FALSE,                     // Underline
        0,                         // StrikeOut
        ANSI_CHARSET,              // CharSet
        OUT_DEFAULT_PRECIS,        // OutPrecision
        CLIP_DEFAULT_PRECIS,       // ClipPrecision
        DEFAULT_QUALITY,           // Quality
        DEFAULT_PITCH | FF_SWISS,  // PitchAndFamily
        WIN_STANDARD_FONT          // Facename
    );
    SendMessage(static_cast<HWND>(handle), WM_SETFONT, (WPARAM)hFont, TRUE);
}

// void WinText::onKeyPress(const uint32_t& key) {
//     callback(key);
// }

void WinText::setTitle(const std::string& title) {
    this->title = title;
    SendMessage(static_cast<HWND>(handle), WM_SETTEXT, 0, (LPARAM)(&this->title));
}

std::string WinText::getTitle() {
    int txtLen = SendMessage(static_cast<HWND>(handle), WM_GETTEXTLENGTH, 0, 0);
    std::unique_ptr<char> buffer(new char[txtLen+1]);
    SendMessage(static_cast<HWND>(handle), WM_GETTEXT, (WPARAM)(txtLen+1), (LPARAM)buffer.get());

    if (!buffer)
        this->title = "";
    this->title = std::string(buffer.get());

    return this->title;
}

PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback) {
    parent->addControl(new WinText(title, *parent, position, size, callback));
    return static_cast<PXText*>(parent->getControls().back());
}
PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback) {
    return createText(title, parent, position, {STD_TEXT_SIZE_WIDTH,STD_TEXT_SIZE_HEIGHT}, callback);
}
#pragma endregion WinText