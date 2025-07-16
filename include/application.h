#pragma once

#include "include/global.h"
#include "include/util.h"
#include "include/controls.h"

#pragma region PXApplication
class LIB PXApplication {
    public:
        virtual int CALL runEventLoop() = 0;
};
using PXApplicationUniquePtr = std::unique_ptr<PXApplication>;
LIB PXApplicationUniquePtr createApplication();
#pragma endregion PXApplication