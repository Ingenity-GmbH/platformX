#pragma once

#include "include/global.h"
#include "include/util.h"
#include "include/controls.h"

#pragma region PXApplication
class LIB PXApplication {
    public:
        virtual void runEventLoop() = 0;
};
using PXApplUniquePtr = std::unique_ptr<PXApplication>;
LIB PXApplication* createApplication();
#pragma endregion PXApplication