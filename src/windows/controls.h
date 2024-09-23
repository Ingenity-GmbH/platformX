#pragma once

#include "include/controls.h"
#include <windows.h>

#pragma region WinButton
class WinButton : public PXButton {
    public:
        WinButton(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback);
        void onClick() override;
        void setTitle(const std::string& title) override;
        std::string getTitle() override;
};
#pragma endregion WinButton

#pragma region WinEdit
class WinEdit : public PXEdit {
    public:
        WinEdit(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        void onKeyPress(const uint32_t& key);
        void setTitle(const std::string& title) override;
        std::string getTitle() override;
};
#pragma endregion WinEdit

#pragma region WinText
class WinText : public PXText {
    public:
        WinText(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
        void setTitle(const std::string& title) override;
        std::string getTitle() override;
};
#pragma endregion WinText
