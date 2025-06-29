#include "include/util.h"

#include <memory>

void util::setFont(const PXHandle& handle) {
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
void util::setTitle(const PXHandle& handle, const std::string& title) {
    SendMessage(static_cast<HWND>(handle), WM_SETTEXT, 0, (LPARAM)(&title));
}

std::string util::getTitle(const PXHandle& handle) {
    int txtLen = SendMessage(static_cast<HWND>(handle), WM_GETTEXTLENGTH, 0, 0);
    std::unique_ptr<char> buffer(new char[txtLen+1]);
    SendMessage(static_cast<HWND>(handle), WM_GETTEXT, (WPARAM)(txtLen+1), (LPARAM)buffer.get());
    
    if (!buffer)
        return "";
    return std::string(buffer.get());
}

void util::setWindowState(const PXHandle& handle, const int32_t& state) {
    ShowWindow(static_cast<HWND>(handle), (int)state);
}

void util::setState(const PXHandle& handle, const bool& state) {
    if (state)
        SendMessage(reinterpret_cast<HWND>(handle), BM_SETCHECK, BST_CHECKED, 0);
    else
        SendMessage(reinterpret_cast<HWND>(handle), BM_SETCHECK, BST_UNCHECKED, 0);
}

bool util::getState(const PXHandle& handle) {
    auto state = SendMessage(reinterpret_cast<HWND>(handle), BM_GETCHECK, 0, 0);
    return state==BST_CHECKED ? true : false;
}

void LIB util::toggleState(const PXHandle& handle) {
    if (getState(handle))
        setState(handle, false);
    else
        setState(handle, true);
}

void util::addItems(const PXHandle& handle, const std::vector<std::string>& items) {
    SendMessage(static_cast<HWND>(handle), LB_RESETCONTENT, 0, 0);
    SendMessage(static_cast<HWND>(handle), CB_RESETCONTENT, 0, 0);

    for (size_t i=0; i<items.size(); i++) {
        SendMessage(static_cast<HWND>(handle), LB_INSERTSTRING, (WPARAM)(i), (LPARAM)(&items[i]));
        SendMessage(static_cast<HWND>(handle), CB_INSERTSTRING , (WPARAM)(i), (LPARAM)(&items[i]));
    }
}

size_t util::getSelectedItem(const PXHandle& handle, const PXType& type) {
    switch (type) {
        case LISTBOX:
            return SendMessage(static_cast<HWND>(handle), LB_GETCURSEL, 0, 0);
        case COMBOBOX:
            return SendMessage(static_cast<HWND>(handle), CB_GETCURSEL, 0, 0);
    } 
    return -1;
}
