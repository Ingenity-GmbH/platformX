#include <windows.h>
#include "include/ui_interface.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class WindowsUI : public UIInterface {
    HWND hwnd;
public:
    void createWindow() override {
        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = "NativeUIWindow";
        RegisterClass(&wc);

        hwnd = CreateWindowEx(
            0, "NativeUIWindow", "Native UI App",
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
            nullptr, nullptr, GetModuleHandle(nullptr), nullptr
        );

        ShowWindow(hwnd, SW_SHOWDEFAULT);
    }

    void showMessage(const char* message) override {
        MessageBoxA(hwnd, message, "Message", MB_OK);
    }

    void runEventLoop() override {
        MSG msg = {};
        while (GetMessage(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

UIInterface* createNativeUI() {
    return new WindowsUI();
}
