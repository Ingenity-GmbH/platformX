#pragma once

#include "include/global.h"
#include "include/controls.h"

#include <string>
#include <memory>

#pragma region PXApplication
class PXApplication {
    public:
        virtual ~PXApplication() = default;
        virtual void runEventLoop() = 0;
        virtual std::shared_ptr<PXControl> getMainWindow() const = 0;
};
PXApplication* createApplication(const std::string& title);
#pragma endregion PXApplication