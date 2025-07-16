 #pragma once

#include <windows.h>
#include <map>
#include "include/controls.h"

#pragma region WinWindow
class LIB WinWindow : public PXWindow {
    public:
        WinWindow(const PXString& title, const bool& isChildWindow, const PXControlSharedPtr& parent=nullptr);
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        void setPosition(const PXPosition& position) override;
        PXPosition getPosition() override;
        void setSize(const PXSize& size) override;
        PXSize getSize() override;

        protected:
            static inline std::map<PXHandle, WinWindow*> handleMap{};
            static inline WinWindow* self = nullptr;
            bool isChildWindow = false;

};
#pragma endregion WinWindow

#pragma region WinMainWindow
class LIB WinMainWindow : public WinWindow {
    public:
        WinMainWindow(const PXString& title);
};
#pragma endregion WinMainWindow

#pragma region WinChildWindow
class LIB WinChildWindow : public WinWindow {
    public:
        WinChildWindow(const PXString& title, PXControlSharedPtr& parent, const PXPosition& position, const PXSize& size);
};
#pragma endregion WinChildWindow
