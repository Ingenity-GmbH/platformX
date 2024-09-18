#pragma once

#include <stdint.h>

const float STD_WIN_SIZE_WIDTH = 1920.0;
const float STD_WIN_SIZE_HEIGHT = 1080.0;
const uint32_t STD_BTN_SIZE_WIDTH = 75;
const uint32_t STD_BTN_SIZE_HEIGHT = 35;

#ifdef _WIN32
    #include <windows.h>
    typedef HWND PXHandle;
#else
    typedef uint32_t PXHandle;
#endif


#pragma region PXType
enum PXType {
    NONE,
    BUTTON,
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
