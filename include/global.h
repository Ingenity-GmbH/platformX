#pragma once

#include <windows.h>
#include <stdint.h>

const float STD_WIN_SIZE_WIDTH = 1920.0;
const float STD_WIN_SIZE_HEIGHT = 1080.0;
const uint32_t STD_BTN_SIZE_WIDTH = 75;
const uint32_t STD_BTN_SIZE_HEIGHT = 35;

typedef HWND Handle;

enum Type {
    NONE,
    BUTTON,
};

struct Position {
    Position(uint32_t x, uint32_t y)
    : x(x), y(y) {}
    uint32_t x, y;
};

struct Size {
    Size(uint32_t width, uint32_t height)
    : width(width), height(height) {}
    uint32_t width, height;
};
