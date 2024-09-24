#pragma once

#include <windows.h>
#include "include/application.h"
#include "include/controls.h"
#include "window.h"

#pragma region WinApplication
class WinApplication : public PXApplication {
    public:
        WinApplication(WinWindow* window);
        void runEventLoop() override;
        std::shared_ptr<PXControl> getMainWindow() const override;

    protected:
        std::shared_ptr<PXWindow> mainWindow;
};
#pragma endregion WinApplication
