 #pragma once

#include <windows.h>
#include "include/components.h"

#pragma region WinButton
class WinButton : public Button {
    public:
        WinButton(const std::string& title, const Position& position, const Component& parent, const std::function<void()>& callback);
        void onClick() override;
};
Button* createButton(const std::string& title, const Position& position, std::shared_ptr<Component> parent, const std::function<void()>& callback);
#pragma endregion Button
