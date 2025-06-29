#pragma once

#include <stdint.h>
#include <memory>

#pragma region base os specific definitions
#if defined(_WIN32)
    // #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #define LIB __declspec(dllexport)
    #include <windows.h>
    using PXHandle = HWND;
    static LPCSTR WIN_STANDARD_FONT = "Segoe UI";
#elif defined(__APPLE__)
    #define LIB __attribute__((visibility("default")))
    #include <AppKit/NSWindow.h>
    using PXHandle = NSWindow*;
#elif defined(__linux__)
    #define LIB __attribute__((visibility("default")))
    #include <X11/Xlib.h>
    using PXHandle = Window;
#else
    #define LIB
    using PXHandle = uint32_t;
#endif
#pragma endregion base os specific definitions

#pragma region global definitions
#define UNIQUE(type, var) std::unique_ptr<type>(var)
#define SHARED(type, var) std::shared_ptr<type>(var)
#pragma endregion global defines

#pragma region global variables
const float STD_MAINWIN_SIZE_WIDTH = 1920.0;
const float STD_MAINWIN_SIZE_HEIGHT = 1080.0;
const float STD_CHILDWIN_SIZE_WIDTH = 480;
const float STD_CHILDWIN_SIZE_HEIGHT = 270;
const uint32_t STD_BTN_SIZE_WIDTH = 75;
const uint32_t STD_BTN_SIZE_HEIGHT = 35;
const uint32_t STD_EDIT_SIZE_WIDTH = 100;
const uint32_t STD_EDIT_SIZE_HEIGHT = 21;
const uint32_t STD_TEXT_SIZE_WIDTH = 100;
const uint32_t STD_TEXT_SIZE_HEIGHT = 18;
const uint32_t STD_LISTBOX_SIZE_WIDTH = 100;
const uint32_t STD_LISTBOX_SIZE_HEIGHT = 75;
const uint32_t STD_COMBOBOX_SIZE_WIDTH = 100;
const uint32_t STD_COMBOBOX_SIZE_HEIGHT = 75;
const uint32_t STD_PROGRESSBAR_SIZE_WIDTH = 100;
const uint32_t STD_PROGRESSBAR_SIZE_HEIGHT = 21;
const uint32_t STD_CHECKBOX_SIZE_WIDTH = 100;
const uint32_t STD_CHECKBOX_SIZE_HEIGHT = 21;
const uint32_t STD_RADIOBUTTON_SIZE_WIDTH = 100;
const uint32_t STD_RADIOBUTTON_SIZE_HEIGHT = 21;
const uint32_t STD_GROUPBOX_SIZE_WIDTH = 200;
const uint32_t STD_GROUPBOX_SIZE_HEIGHT = 300;
#pragma endregion global variables

#pragma region PXType
enum PXType {
    NONE,
    WINDOW,
    BUTTON,
    EDIT,
    TEXT,
    LISTBOX,
    COMBOBOX,
    GROUPBOX
};
#pragma endregion PXType

#pragma region PXPosition
struct PXPosition {
    PXPosition(uint32_t x, uint32_t y)
    : x(x), y(y) {}
    uint32_t x, y;

    PXPosition& operator+=(const PXPosition& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
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
