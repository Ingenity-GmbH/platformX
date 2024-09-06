#pragma once

#include <string>

class UIInterface {
    public:
        virtual ~UIInterface() = default;
        virtual void createWindow(const std::string& windowTitle) = 0;
        virtual void runEventLoop() = 0;

    protected:
        std::string windowTitle;

};

UIInterface* createUI();
