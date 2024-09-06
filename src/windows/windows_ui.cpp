#include "windows_ui.h"

#include "include/global.h"

#pragma region WindowsUI
void WindowsUI::createWindow(const std::string& windowTitle) {
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WindowProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = GetModuleHandle(nullptr);;
    // wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    // wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    // wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    std::wstring wstr(windowTitle.begin(), windowTitle.end());
    wcex.lpszClassName  =  wstr.c_str();
    // wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    hWnd = CreateWindowW(   wcex.lpszClassName , 
                            wcex.lpszClassName ,
                            WS_OVERLAPPEDWINDOW,
                            (width-std::min<int>(width,STD_WIN_SIZE_WIDTH))/2.0, 
                            (height-std::min<int>(height,STD_WIN_SIZE_HEIGHT))/2.0,
                            std::min<int>(width,STD_WIN_SIZE_WIDTH),
                            std::min<int>(height,STD_WIN_SIZE_HEIGHT),
                            nullptr,
                            nullptr,
                            wcex.hInstance,
                            nullptr);

    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
}

void WindowsUI::runEventLoop() {
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
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

UIInterface* createUI() {
    return new WindowsUI();
}
#pragma endregion WindowsUI
