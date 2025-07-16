
#include "include/global.h"
#include "include/util.h"
#include "controls.h"
#include "window.h"
#include <uxtheme.h>
#include <vssym32.h>

#pragma region WinWindow
WinWindow::WinWindow(const PXString& title, const bool& isChildWindow, const PXControlSharedPtr& parent) 
: PXWindow(
    title, 
    PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_MAINWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_MAINWIN_SIZE_HEIGHT))/2.0),
    PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_MAINWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_MAINWIN_SIZE_HEIGHT))) {

    this->isChildWindow = isChildWindow;
    this->parent = parent.get();
    self = this;

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(wc);
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    if (isChildWindow)
        wc.hInstance = reinterpret_cast<HINSTANCE>(parent->getHandle());
    else
        wc.hInstance = GetModuleHandle(nullptr);
        // wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
        // wc.hCursor  = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        // wc.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
        wc.lpszClassName = L"WinWindow";
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

    WinWindow::handleMap.insert({handle, self});
    util::setFont(handle);

    if (isChildWindow) {
        SetWindowLong(handle, GWL_STYLE, (GetWindowLong(handle, GWL_STYLE) & ~WS_POPUP) | WS_CHILD);
        SetParent(handle, reinterpret_cast<HWND>(parent->getHandle()));
    }
    else {
        ShowWindow(handle, SW_SHOWDEFAULT);
        UpdateWindow(handle);
    }
}

LRESULT CALLBACK WinWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    
    try {
        self = WinWindow::handleMap.at(hWnd);
    } catch (...) {}

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
        case WM_SIZE:
            {
                for (const auto& control : self->controls) {
                    if (control->getType() == STATUSBAR) {
                        auto statusbar = reinterpret_cast<WinStatusBar*>(control);
                        SendMessage(statusbar->getHandle(), WM_SIZE, 0, 0);
                        statusbar->setSize({static_cast<uint32_t>(LOWORD(lParam)), statusbar->getSize().height});
                        statusbar->updateParts();
                    }else if(control->getType() == TOOLBAR){
                        auto toolbar = reinterpret_cast<WinToolBar*>(control);
                        SendMessage(toolbar->getHandle(), WM_SIZE, 0, 0);
                        toolbar->setSize({static_cast<uint32_t>(LOWORD(lParam)), toolbar->getSize().height});
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
        case WM_CLOSE:
            if (self->isChildWindow)
                ShowWindow(hWnd, SW_HIDE);
            else
                DestroyWindow(hWnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam); 
}

void WinWindow::setPosition(const PXPosition& position) {
    PXControl::setPosition(position);
    SetWindowPos(handle, NULL, position.x, position.y, size.width, size.height, SWP_NOZORDER);
}

PXPosition WinWindow::getPosition() {
    RECT rect;
    GetWindowRect(handle, &rect);
    size = {static_cast<uint32_t>(rect.right - rect.left), static_cast<uint32_t>(rect.bottom - rect.top)};
    position = {static_cast<uint32_t>(rect.left), static_cast<uint32_t>(rect.top)};
    return PXControl::getPosition();
}

void WinWindow::setSize(const PXSize& size) {
    PXControl::setSize(size);
    setPosition(position);
}

PXSize WinWindow::getSize() {
    getPosition();
    return PXControl::getSize();
}
#pragma endregion WinWindow

#pragma region WinMainWindow
WinMainWindow::WinMainWindow(const PXString& title) : WinWindow(title, false) {}

PXWindowSharedPtr createMainWindow(const PXString& title) {
    return PXWindowSharedPtr(new WinMainWindow(title));
}
#pragma endregion WinMainWindow

#pragma region WinChildWindow
WinChildWindow::WinChildWindow(const PXString& title, PXControlSharedPtr& parent, const PXPosition& position, const PXSize& size) :  WinWindow(title, true, parent) {
    setPosition(position);
    setSize(size);
}

PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size) {
    parent->addControl(new WinChildWindow(title, parent, position, size));
    return PXWindowSharedPtr(reinterpret_cast<PXWindow*>(parent->getControls().back()));
}

PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXPosition& position) {
    return createWindow(title, parent, position, PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT)));
}

PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXSize& size) {
    return createWindow(title, parent, PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT))/2.0), size);
}

PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent) {
    return createWindow(title, parent, PXPosition((GetSystemMetrics(SM_CXSCREEN)-std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH))/2.0, (GetSystemMetrics(SM_CYSCREEN)-std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT))/2.0), PXSize(std::min<int>(GetSystemMetrics(SM_CXSCREEN),STD_CHILDWIN_SIZE_WIDTH), std::min<int>(GetSystemMetrics(SM_CYSCREEN),STD_CHILDWIN_SIZE_HEIGHT)));
}
#pragma endregion WinMainWindow
