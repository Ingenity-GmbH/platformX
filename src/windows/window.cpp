
#include "window.h"
#include "include/global.h"
#include "button.h"

#pragma region Window
WinWindow::WinWindow(const std::string& title) 
: Window(
    title, 
    Position((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_WIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_WIN_SIZE_HEIGHT))/2.0),
    Size(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_WIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_WIN_SIZE_HEIGHT))) {

    self = this;
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(nullptr);;
    // wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wcex.hCursor  = LoadCursor(nullptr, IDC_ARROW);
    // wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    // wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    std::wstring wstr(this->title.begin(), this->title.end());
    wcex.lpszClassName = wstr.c_str();
    // wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    handle = reinterpret_cast<Handle>(CreateWindowW(
        wcex.lpszClassName , 
        wcex.lpszClassName ,
        WS_OVERLAPPEDWINDOW,
        position.x, 
        position.y,
        size.width,
        size.height,
        nullptr,
        nullptr,
        wcex.hInstance,
        nullptr));

    ShowWindow(reinterpret_cast<HWND>(handle), SW_SHOWDEFAULT);
    UpdateWindow(reinterpret_cast<HWND>(handle));
}

LRESULT CALLBACK WinWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND:
            {
                for (const auto& component : self->components) {
                    if (component.getType() == BUTTON) {
                        auto btn = (Button*)(&component);
                        btn->onClick();
                    }
                }
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
