#include "application.h"
#include "window.h"

#pragma region WinApplication
WinApplication::WinApplication(WinWindow* window)
: mainWindow(window) {}

void WinApplication::runEventLoop() {
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

std::shared_ptr<PXControl> WinApplication::getMainWindow() const {
    return mainWindow;
}

PXApplication* createApplication(PXWindow* window) {
    return new WinApplication(static_cast<WinWindow*>(window));
}
#pragma endregion WinApplication
