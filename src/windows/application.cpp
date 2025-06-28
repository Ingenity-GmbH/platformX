#include "application.h"
#include "window.h"

#pragma region WinApplication
WinApplication::WinApplication(PXWindowSharedPtr window) {}

void WinApplication::runEventLoop() {
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

PXApplication* createApplication(PXWindowSharedPtr window) {
    return new WinApplication(window);
}
#pragma endregion WinApplication
