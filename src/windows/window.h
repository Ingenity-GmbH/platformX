 #pragma once

#include <windows.h>
#include "include/controls.h"

#pragma region WinMainWindow
class LIB WinMainWindow : public PXWindow {
    public:
        WinMainWindow(const std::string& title);
        ~WinMainWindow() override;
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        static inline WinMainWindow* self = nullptr;
};
#pragma endregion WinMainWindow

#pragma region WinChildWindow
class LIB WinChildWindow : public PXWindow {
    public:
        WinChildWindow(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size);
        ~WinChildWindow() override;
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        static inline WinChildWindow* self = nullptr;
};
#pragma endregion WinChildWindow
