#include "application.h"
#include "window.h"

#pragma region WinApplication
WinApplication::WinApplication(const std::string& title)
: mainWindow(createWindow(title)) {}

void WinApplication::runEventLoop() {
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

std::shared_ptr<Component> WinApplication::getWindow() const {
    return mainWindow;
}

Application* createApplication(const std::string& title) {
    return new WinApplication(title);
}
#pragma endregion WinApplication
