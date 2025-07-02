
#include "include/global.h"
#include "include/util.h"
#include "controls.h"
#include "window.h"
#include <uxtheme.h>
#include <vssym32.h>

#pragma region WinMainWindow
WinMainWindow::WinMainWindow(const PXString& title) 
: PXWindow(
    title, 
    PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_MAINWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_MAINWIN_SIZE_HEIGHT))/2.0),
    PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_MAINWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_MAINWIN_SIZE_HEIGHT))) {

    self = this;

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(wc);
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(nullptr);
    // wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wc.hCursor  = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // wc.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wc.lpszClassName = L"MainWindow";
    // wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassEx(&wc);

    handle = CreateWindowEx(
        0,
        wc.lpszClassName,
        this->title.toLPCWSTR(),
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        position.x, 
        position.y,
        size.width,
        size.height,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr);

    util::setFont(handle);

    ShowWindow(handle, SW_SHOWDEFAULT);
    UpdateWindow(handle);
}

LRESULT CALLBACK WinMainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    HWND hwndChild;

    switch (message) {
        case WM_COMMAND:
            {
                for (const auto& control : self->controls) {
                    if (control->hasCallback() && control->getType() == BUTTON && control->getHandle() == reinterpret_cast<PXHandle>(lParam)) {
                        auto btn = reinterpret_cast<WinButton*>(control);
                        btn->onClick();
                    }
                    else if (control->hasCallback() && control->getType() == EDIT && control->getHandle() == reinterpret_cast<PXHandle>(lParam)) {
                        auto edit = reinterpret_cast<WinEdit*>(control);
                        edit->onKeyPress(reinterpret_cast<const uint32_t&>(wParam));
                    }
                }
                break;
            }
        case WM_NOTIFY:
            {
                LPNMHDR pnmhdr = (LPNMHDR)lParam;
                for (const auto& control : self->controls) {
                    if (control->hasCallback() && control->getType() == TREEVIEW && control->getHandle() == reinterpret_cast<PXHandle>(pnmhdr->hwndFrom) && pnmhdr->code == TVN_SELCHANGED) {
                        auto treeview = reinterpret_cast<WinTreeView*>(control);
                        treeview->onClick();
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

PXWindow* createMainWindow(const PXString& title) {
    return new WinMainWindow(title);
}
#pragma endregion WinMainWindow

#pragma region WinChildWindow
WinChildWindow::WinChildWindow(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size)
: PXWindow(
    title,
    position,
    size) {

    self = this;
    this->parent = parent.get();

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(wc);
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = reinterpret_cast<HINSTANCE>(parent->getHandle());
    // wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // wc.hCursor  = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // wc.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wc.lpszClassName = L"ChildWindow";
    // wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassEx(&wc);

    handle = CreateWindowEx(
        0,
        wc.lpszClassName, 
        this->title.toLPCWSTR(),
        WS_OVERLAPPEDWINDOW,
        position.x, 
        position.y,
        size.width,
        size.height,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr);

    util::setFont(handle);

    SetWindowLong(handle, GWL_STYLE, (GetWindowLong(handle, GWL_STYLE) & ~WS_POPUP) | WS_CHILD);
    SetParent(handle, reinterpret_cast<HWND>(parent->getHandle()));
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
                        auto btn = reinterpret_cast<WinButton*>(control);
                        btn->onClick();
                    }
                    else if (control->hasCallback() && control->getType() == EDIT && control->getHandle() == reinterpret_cast<PXHandle>(lParam)) {
                        auto edit = reinterpret_cast<WinEdit*>(control);
                        edit->onKeyPress(reinterpret_cast<const uint32_t&>(wParam));
                    }
                }
                break;
            }
        case WM_NOTIFY:
            {
                LPNMHDR pnmhdr = (LPNMHDR)lParam;
                for (const auto& control : self->controls) {
                    if (control->hasCallback() && control->getType() == TREEVIEW && control->getHandle() == reinterpret_cast<PXHandle>(pnmhdr->hwndFrom) && pnmhdr->code == TVN_SELCHANGED) {
                        auto treeview = reinterpret_cast<WinTreeView*>(control);
                        treeview->onClick();
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

PXWindow* createWindow(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size) {
    parent->addControl(new WinChildWindow(title, parent, position, size));
    return reinterpret_cast<PXWindow*>(parent->getControls().back());
}

PXWindow* createWindow(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position) {
    return createWindow(title, parent, position, PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT)));
}

PXWindow* createWindow(const PXString& title, std::shared_ptr<PXControl> parent, const PXSize& size) {
    return createWindow(title, parent, PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT))/2.0), size);
}

PXWindow* createWindow(const PXString& title, std::shared_ptr<PXControl> parent) {
    return createWindow(title, parent, PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT))/2.0), PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT)));
}
#pragma endregion WinMainWindow
