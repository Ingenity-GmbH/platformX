#include "application.h"
#include "window.h"

#pragma region WinApplication
int WINAPI WinApplication::runEventLoop() {
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}

PXApplUniquePtr createApplication() {
    return std::unique_ptr<PXApplication>(new WinApplication());
}
#pragma endregion WinApplication
