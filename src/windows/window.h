 #pragma once

#include <windows.h>
#include "include/controls.h"

#pragma region WinWindow
class WinWindow : public PXWindow {
    public:
        WinWindow(const std::string& title);
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        void setTitle(const std::string& title) override;
        std::string getTitle() override;

    protected:
        static inline WinWindow* self = nullptr;
};
#pragma endregion WinWindow
