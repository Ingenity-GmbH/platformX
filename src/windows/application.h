#pragma once

#include <windows.h>
#include "include/application.h"
#include "include/controls.h"
#include "window.h"

#pragma region WinApplication
class LIB WinApplication : public PXApplication {
    public:
        int WINAPI runEventLoop() override;
};
#pragma endregion WinApplication
