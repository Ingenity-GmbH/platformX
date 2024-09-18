#pragma once

#include <windows.h>
#include "include/application.h"
#include "include/components.h"

#pragma region WinApplication
class WinApplication : public PXApplication {
    public:
        WinApplication(const std::string& title);
        void runEventLoop() override;
        std::shared_ptr<PXComponent> getMainWindow() const override;

    protected:
        std::shared_ptr<PXWindow> mainWindow;
};
#pragma endregion WinApplication
