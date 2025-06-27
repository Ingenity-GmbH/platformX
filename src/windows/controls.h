#pragma once

#include "include/controls.h"
#include <windows.h>

#pragma region WinButton
class LIB WinButton : public PXButton {
    public:
        WinButton(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback);
        void onClick() override;
};
#pragma endregion WinButton

#pragma region WinEdit
class LIB WinEdit : public PXEdit {
    public:
        WinEdit(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        void onKeyPress(const uint32_t& key);
};
#pragma endregion WinEdit

#pragma region WinText
class LIB WinText : public PXText {
    public:
        WinText(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
};
#pragma endregion WinText

#pragma region WinListBox
class LIB WinListBox : public PXListBox {
    public:
        WinListBox(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
        void addItem(const std::string& title, const size_t& pos) override;
        void removeItem(const size_t& pos) override;
        size_t getSelectedItem() const override;
};
#pragma endregion WinListBox

#pragma region WinComboBox
class LIB WinComboBox : public PXComboBox {
    public:
        WinComboBox(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
        void addItem(const std::string& title, const size_t& pos) override;
        void removeItem(const size_t& pos) override;
        size_t getSelectedItem() const override;
};
#pragma endregion WinComboBox

#pragma region WinProgressBar
class LIB WinProgressBar : public PXProgressBar {
    public:
        WinProgressBar(const std::string& title, const PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
        void configure(const uint32_t& min, const uint32_t& max, const uint32_t& step) override;
        void incStep() override;
        void setPos(const uint32_t& pos) override;
        void setColor(const PXColor& front, const PXColor& back) override;
};
#pragma endregion WinProgressBar
