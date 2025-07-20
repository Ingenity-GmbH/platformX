#pragma once
#include "include/application.h"

#pragma region MacOSApplication
class MacOSApplication : public PXApplication {
    public:
        MacOSApplication();
        ~MacOSApplication() override;
        int runEventLoop() override;

    protected:
        std::shared_ptr<PXWindow> mainWindow;
        PXHandle pApp;
        PXHandle pAppDelegate;
};
#pragma endregion MacOSApplication
