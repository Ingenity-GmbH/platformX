
#include "include/global.h"
#include "include/util.h"
#include "controls.h"
#include "window.h"
#include <uxtheme.h>
#include <vssym32.h>

#pragma region WinMainWindow
WinMainWindow::WinMainWindow(const std::string& title) 
: PXWindow(
    title, 
    PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_MAINWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_MAINWIN_SIZE_HEIGHT))/2.0),
    PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_MAINWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_MAINWIN_SIZE_HEIGHT))) {

    self = this;

    WNDCLASSA wc = {};
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(nullptr);
    // wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wc.hCursor  = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // wc.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wc.lpszClassName = "MainWindow";
    // wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassA(&wc);

    handle = static_cast<PXHandle>(CreateWindowA(
        wc.lpszClassName, 
        this->title.c_str(),
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        position.x, 
        position.y,
        size.width,
        size.height,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr));

    util::setFont(handle);

    ShowWindow(static_cast<HWND>(handle), SW_SHOWDEFAULT);
    UpdateWindow(static_cast<HWND>(handle));
}

WinMainWindow::~WinMainWindow() {
    for (PXControl* control : controls) {
        if (control) {
            delete control;
            control = nullptr;
        }
    }
}

LRESULT CALLBACK WinMainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    HWND hwndChild;

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
        // case WM_PAINT:
        //     {
        //         hdc = BeginPaint(hWnd, &ps);
        //         EndPaint(hWnd, &ps);
        //         break;
        //     }
        // case WM_DRAWITEM:
        //     {
        //         hdc = BeginPaint(hWnd, &ps);
        //         EndPaint(hWnd, &ps);
        //         break;
        //     }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam); 
}

PXWindow* createMainWindow(const std::string& title) {
    return new WinMainWindow(title);
}
#pragma endregion WinMainWindow

#pragma region WinChildWindow
WinChildWindow::WinChildWindow(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size)
: PXWindow(
    title,
    position,
    size) {

    self = this;

    WNDCLASSA wc = {};
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = reinterpret_cast<HINSTANCE>(parent->getHandle());
    // wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wc.hCursor  = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // wc.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wc.lpszClassName = "ChildWindow";
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

    util::setFont(handle);

    SetWindowLong(reinterpret_cast<HWND>(handle), GWL_STYLE, (GetWindowLong(reinterpret_cast<HWND>(handle), GWL_STYLE) & ~WS_POPUP) | WS_CHILD);
    SetParent(reinterpret_cast<HWND>(handle), reinterpret_cast<HWND>(parent->getHandle()));
}

WinChildWindow::~WinChildWindow() {
    for (PXControl* control : controls) {
        if (control) {
            delete control;
            control = nullptr;
        }
    }
}

LRESULT CALLBACK WinChildWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

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
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            ShowWindow(reinterpret_cast<HWND>(self->getHandle()), SW_HIDE);
            return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam); 
}

PXWindow* createWindow(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size) {
    parent->addControl(new WinChildWindow(title, parent, position, size));
    return static_cast<PXWindow*>(parent->getControls().back());
}

PXWindow* createWindow(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position) {
    return createWindow(title, parent, position, PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT)));
}

PXWindow* createWindow(const std::string& title, std::shared_ptr<PXControl> parent, const PXSize& size) {
    return createWindow(title, parent, PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT))/2.0), size);
}

PXWindow* createWindow(const std::string& title, std::shared_ptr<PXControl> parent) {
    return createWindow(title, parent, PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT))/2.0), PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT)));
}
#pragma endregion WinMainWindow
