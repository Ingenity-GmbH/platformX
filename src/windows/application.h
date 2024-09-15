#pragma once

#include <windows.h>
#include "include/application.h"
#include "include/components.h"

#pragma region WinApplication
class WinApplication : public Application {
    public:
        WinApplication(const std::string& title);
        void runEventLoop() override;
        std::shared_ptr<Component> getMainWindow() const override;

    protected:
        std::shared_ptr<Window> mainWindow;
};
Application* createApplication(const std::string& title);
#pragma endregion WinApplication
