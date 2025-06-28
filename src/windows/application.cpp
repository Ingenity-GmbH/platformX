#include "application.h"
#include "window.h"

#pragma region WinApplication
void WinApplication::runEventLoop() {
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

PXApplication* createApplication() {
    return new WinApplication();
}
#pragma endregion WinApplication
