#pragma once

class UIInterface {
public:
    virtual ~UIInterface() = default;
    virtual void createWindow() = 0;
    virtual void showMessage(const char* message) = 0;
    virtual void runEventLoop() = 0;
};

UIInterface* createNativeUI();
