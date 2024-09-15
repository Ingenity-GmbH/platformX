 #pragma once

#include <windows.h>
#include "include/components.h"

#pragma region WinWindow
class WinWindow : public Window {
    public:
        WinWindow(const std::string& title);
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        static inline WinWindow* self = nullptr;
};
Window* createWindow(const std::string& title);
#pragma endregion WinWindow
