#pragma once

#include <windows.h>
#include "include/application.h"
#include "include/controls.h"
#include "window.h"

#pragma region WinApplication
class LIB WinApplication : public PXApplication {
    public:
        WinApplication(PXWindowSharedPtr window);
        void runEventLoop() override;
};
#pragma endregion WinApplication
