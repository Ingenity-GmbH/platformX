
#include "include/global.h"
#include "controls.h"
#include "window.h"

#pragma region WinWindow
WinWindow::WinWindow(const std::string& title) 
: PXWindow(
    title, 
    PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_WIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_WIN_SIZE_HEIGHT))/2.0),
    PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_WIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_WIN_SIZE_HEIGHT))) {

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

    handle = static_cast<PXHandle>(CreateWindowA(
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
                for (const auto control : self->controls) {
                    if (control->hasCallback() && control->getType() == BUTTON && control->getHandle() == reinterpret_cast<PXHandle>(lParam)) {
                        auto btn = static_cast<WinButton*>(control);
                        btn->onClick();
                    }
                    else if (control->hasCallback() && control->getType() == EDIT && control->getHandle() == reinterpret_cast<PXHandle>(lParam)) {
                        auto edit = static_cast<WinEdit*>(control);
                        edit->onKeyPress(static_cast<const uint32_t&>(wParam));
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

void WinWindow::setTitle(const std::string& title) {
    this->title = title;
    SendMessage(static_cast<HWND>(handle), WM_SETTEXT, 0, (LPARAM)(&this->title));
}

std::string WinWindow::getTitle() {
    int txtLen = SendMessage(static_cast<HWND>(handle), WM_GETTEXTLENGTH, 0, 0);
    std::unique_ptr<char> buffer(new char[txtLen+1]);
    SendMessage(static_cast<HWND>(handle), WM_GETTEXT, (WPARAM)(txtLen+1), (LPARAM)buffer.get());

    if (!buffer)
        this->title = "";
    this->title = std::string(buffer.get());

    return this->title;
}

PXWindow* createWindow(const std::string& title) {
    return new WinWindow(title);
}
#pragma endregion WinWindow
