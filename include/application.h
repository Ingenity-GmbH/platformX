#pragma once

#include "include/global.h"
#include "include/controls.h"
#include "include/util.h"

#include <string>
#include <memory>

#pragma region PXApplication
class LIB PXApplication {
    public:
        virtual void runEventLoop() = 0;
};
using PXApplUniquePtr = std::unique_ptr<PXApplication>;
LIB PXApplication* createApplication();
#pragma endregion PXApplication