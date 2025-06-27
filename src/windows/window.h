 #pragma once

#include <windows.h>
#include "include/controls.h"

#pragma region WinWindow
class LIB WinWindow : public PXWindow {
    public:
        WinWindow(const std::string& title);
        ~WinWindow() override;
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        static inline WinWindow* self = nullptr;
};
#pragma endregion WinWindow
