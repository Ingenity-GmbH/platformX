#pragma once

#include <windows.h>
#include <algorithm>

#include "include/ui_interface.h"

#pragma region WindowsUI
class WindowsUI : public UIInterface {
    public:
        void createWindow(const std::string& windowTitle) override;
        void runEventLoop() override;

    private:
        HWND hWnd;

};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
UIInterface* createUI();
#pragma endregion WindowsUI
