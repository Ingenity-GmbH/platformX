#pragma once

#include <stdint.h>
#include <string>

#pragma region base os specific definitions
#if defined(_WIN32)
    // #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #define LIB __declspec(dllexport)
    #define CALL WINAPI 
    #include <windows.h>
    #include <memory>
    #include <CommCtrl.h>
    #include <prsht.h>
    using PXHandle = HWND;
    using PXNodeHandle = HTREEITEM;
    static LPCWSTR WIN_STANDARD_FONT = L"Segoe UI";
#elif defined(__linux__)
    #define LIB
    #define CALL
    #include <X11/Xlib.h>
    using PXHandle = Window;
    using PXNodeHandle = XID;
#elif defined(__APPLE__)
    #define LIB
    #define CALL
    #include <AppKit/AppKit.h>
    using PXHandle = void*;
    using PXNodeHandle = uint32_t;
#else
    #define LIB
    #define CALL
    using PXHandle = uint32_t;
    using PXNodeHandle = uint32_t;
#endif
#pragma endregion base os specific definitions

#pragma region global definitions
#define EMPTY ""
using UTF8_t = const char*;
using Unicode_t = const wchar_t*;
#pragma endregion global defines

#pragma region general control dimensions
const float STD_MAINWIN_SIZE_WIDTH = 1920.0;
const float STD_MAINWIN_SIZE_HEIGHT = 1080.0;
const float STD_CHILDWIN_SIZE_WIDTH = 480;
const float STD_CHILDWIN_SIZE_HEIGHT = 270;
const uint32_t STD_BTN_SIZE_WIDTH = 100;
const uint32_t STD_BTN_SIZE_HEIGHT = 40;
const uint32_t STD_EDIT_SIZE_WIDTH = 100;
const uint32_t STD_EDIT_SIZE_HEIGHT = 21;
const uint32_t STD_TEXT_SIZE_WIDTH = 100;
const uint32_t STD_TEXT_SIZE_HEIGHT = 18;
const uint32_t STD_LISTBOX_SIZE_WIDTH = 200;
const uint32_t STD_LISTBOX_SIZE_HEIGHT = 200;
const uint32_t STD_TREEVIEW_SIZE_WIDTH = 200;
const uint32_t STD_TREEVIEW_SIZE_HEIGHT = 200;
const uint32_t STD_COMBOBOX_SIZE_WIDTH = 200;
const uint32_t STD_COMBOBOX_SIZE_HEIGHT = 200;
const uint32_t STD_PROGRESSBAR_SIZE_WIDTH = 200;
const uint32_t STD_PROGRESSBAR_SIZE_HEIGHT = 21;
const uint32_t STD_CHECKBOX_SIZE_WIDTH = 100;
const uint32_t STD_CHECKBOX_SIZE_HEIGHT = 21;
const uint32_t STD_RADIOBUTTON_SIZE_WIDTH = 100;
const uint32_t STD_RADIOBUTTON_SIZE_HEIGHT = 21;
const uint32_t STD_GROUPBOX_SIZE_WIDTH = 200;
const uint32_t STD_GROUPBOX_SIZE_HEIGHT = 200;
const uint32_t STD_SPIN_SIZE_WIDTH = 35;
const uint32_t STD_SPIN_SIZE_HEIGHT = 21;
#pragma endregion general control dimensions

#pragma region PXType
enum PXType {
    NONE,
    WINDOW,
    BUTTON,
    EDIT,
    TEXT,
    LISTBOX,
    COMBOBOX,
    GROUPBOX,
    TREEVIEW,
    STATUSBAR
};
#pragma endregion PXType

#pragma region PXString
class LIB PXString {
    private:
        void cast();
        std::string str;
        std::wstring wstr;

    public:
        PXString();
        PXString(const std::string& str);
        PXString(const std::wstring& wstr);
        PXString(const char* str);
        PXString(const wchar_t* wstr);

        std::string toString() const;
        std::wstring toWstring() const;
        UTF8_t toUTF8() const;
        Unicode_t toUnicode() const;
       
        PXString& operator=(const PXString& other);
        friend LIB PXString operator+(const PXString& lhs, const PXString& rhs);
};
LIB PXString operator+(const PXString& lhs, const PXString& rhs);
#pragma endregion PXString

#pragma region PXPosition
struct LIB PXPosition {
    PXPosition(uint32_t x, uint32_t y);
    uint32_t x, y;

    PXPosition& operator+=(const PXPosition& other);
};
#pragma endregion PXPosition

#pragma region PXSize
struct PXSize {
    PXSize(uint32_t width, uint32_t height)
    : width(width), height(height) {}
    uint32_t width, height;
};
#pragma endregion PXSize

#pragma region PXColor
struct PXColor {
    PXColor(uint8_t r, uint8_t g, uint8_t b)
    : r(r), g(g), b(b) {}
    uint8_t r, g, b;
};
#pragma endregion PXColor

#pragma region PXNode
struct PXNode {
    PXNode(PXString title, PXNode* parent=nullptr)
    : title(title), parent(parent) {}
    PXString title;
    PXNodeHandle handle;
    PXNode* parent;
};
#pragma endregion PXNode

#pragma region PXStatusBarPart
struct PXStatusBarPart {
    PXStatusBarPart(const double& relEndPos, const PXString& text)
    : relEndPos(relEndPos), text(text) {}
    double relEndPos;
    PXString text;
};
#pragma endregion PXStatusBarPart
