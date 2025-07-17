#pragma once

#include <X11/Xlib.h>

#include "include/application.h"

#pragma region LinuxUI
class LinuxUI : public PXApplication {
    public:
        void createWindow();
        int runEventLoop() override;
    
    private:
        Display* display;
        Window window;
};

PXApplication* createNativeUI();
#pragma endregion LinuxUI
