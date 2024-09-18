 #pragma once

#include <windows.h>
#include "include/components.h"

#pragma region WinButton
class WinButton : public PXButton {
    public:
        WinButton(const std::string& title, const PXPosition& position, const PXComponent& parent, const std::function<void()>& callback);
        void onClick() override;
};
#pragma endregion WinButton
