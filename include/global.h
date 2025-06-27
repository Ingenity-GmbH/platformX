#pragma once

#include <stdint.h>

#ifdef _WIN32
    // #pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #define LIB __declspec(dllexport)
    #include <windows.h>
    typedef HWND PXHandle;
    static LPCSTR WIN_STANDARD_FONT = "Segoe UI";
#else
    typedef uint32_t PXHandle;
#endif

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
#pragma endregion global variables

#pragma region PXType
enum PXType {
    NONE,
    BUTTON,
    EDIT,
    TEXT,
    LISTBOX,
    COMBOBOX
};
#pragma endregion PXType

#pragma region PXPosition
struct PXPosition {
    PXPosition(uint32_t x, uint32_t y)
    : x(x), y(y) {}
    uint32_t x, y;
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
