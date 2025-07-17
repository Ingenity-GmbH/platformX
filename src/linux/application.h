#pragma once

#include "include/application.h"
#include "include/controls.h"

#pragma region LinuxApplication
class LIB LinuxApplication : public PXApplication {
    public:
        int runEventLoop() override;

    protected:
        Display* display = nullptr;
        PXHandle mainWnd;
};
#pragma endregion LinuxUI
