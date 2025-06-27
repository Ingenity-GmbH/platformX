#pragma once

#include "include/global.h"
#include "include/controls.h"
#include "include/util.h"

#include <string>
#include <memory>

#pragma region PXApplication
class LIB PXApplication {
    public:
        virtual ~PXApplication() = default;
        virtual void runEventLoop() = 0;
        virtual std::shared_ptr<PXControl> getMainWindow() const = 0;
};
LIB PXApplication* createApplication(PXWindow* window);
#pragma endregion PXApplication