#pragma once

#include <X11/Xlib.h>

#include "include/ui_interface.h"

#pragma region LinuxUI
class LinuxUI : public UIInterface {
    public:
        void createWindow() override;
        void runEventLoop() override;
    
    private:
        Display* display;
        Window window;
};

UIInterface* createNativeUI();
#pragma endregion LinuxUI
