
#include "window.h"
#include "include/global.h"
#include "button.h"

#pragma region Window
WinWindow::WinWindow(const std::string& title) 
: Window(
    title, 
    Size(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_WIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_WIN_SIZE_HEIGHT)),
    Position((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_WIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_WIN_SIZE_HEIGHT))/2.0)) {

    self = this;
    WNDCLASSA wc = {};

    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(nullptr);;
    // wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wc.hCursor  = LoadCursor(nullptr, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    // wc.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wc.lpszClassName = "MainWindow";
    // wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassA(&wc);

    handle = static_cast<Handle>(CreateWindowA(
        wc.lpszClassName, 
        this->title.c_str(),
        WS_OVERLAPPEDWINDOW,
        position.x, 
        position.y,
        size.width,
        size.height,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr));

    ShowWindow(static_cast<HWND>(handle), SW_SHOWDEFAULT);
    UpdateWindow(static_cast<HWND>(handle));
}

LRESULT CALLBACK WinWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND:
            {
                for (const auto component : self->components) {
                    if (component->getType() == BUTTON && component->getHandle() == reinterpret_cast<Handle>(lParam)) {
                        auto btn = static_cast<WinButton*>(component);
                        btn->onClick();
                    }
                }
                break;
            }
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                EndPaint(hWnd, &ps);
                break;
            }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam); 
}

Window* createWindow(const std::string& title) {
    return new WinWindow(title);
}
#pragma endregion Window
