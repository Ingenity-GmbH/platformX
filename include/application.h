#pragma once

#include "include/global.h"
#include "include/application.h"
#include "include/components.h"

#include <string>
#include <memory>

class Application {
    public:
        virtual ~Application() = default;
        virtual void runEventLoop() = 0;
        virtual std::shared_ptr<Component> getWindow() const = 0;
};
Application* createApplication(const std::string& title);
