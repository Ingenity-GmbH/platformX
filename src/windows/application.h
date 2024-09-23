#pragma once

#include <windows.h>
#include "include/application.h"
#include "include/controls.h"

#pragma region WinApplication
class WinApplication : public PXApplication {
    public:
        WinApplication(const std::string& title);
        void runEventLoop() override;
        std::shared_ptr<PXControl> getMainWindow() const override;

    protected:
        std::shared_ptr<PXWindow> mainWindow;
};
#pragma endregion WinApplication
