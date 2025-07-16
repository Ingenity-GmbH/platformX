#pragma once

#include "include/controls.h"
#include <windows.h>

#pragma region WinButton
class LIB WinButton : public PXButton {
    public:
        WinButton(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback);
        void onClick() override;
};
#pragma endregion WinButton

#pragma region WinEdit
class LIB WinEdit : public PXEdit {
    public:
        WinEdit(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        void onKeyPress(const uint32_t& key);
};
#pragma endregion WinEdit

#pragma region WinText
class LIB WinText : public PXText {
    public:
        WinText(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
};
#pragma endregion WinText

#pragma region WinListBox
class LIB WinListBox : public PXListBox {
    public:
        WinListBox(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
        void addNode(PXNode& node, const size_t& pos) override;
        void removeNode(const size_t& pos) override;
        const PXNode* getSelectedNode() const override;
};
#pragma endregion WinListBox

#pragma region WinComboBox
class LIB WinComboBox : public PXComboBox {
    public:
        WinComboBox(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
        void addNode(PXNode& node, const size_t& pos) override;
        void removeNode(const size_t& pos) override;
        const PXNode* getSelectedNode() const override;
};
#pragma endregion WinComboBox

#pragma region WinProgressBar
class LIB WinProgressBar : public PXProgressBar {
    public:
        WinProgressBar(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback);
        // void onKeyPress(const uint32_t& key) override;
        void configure(const uint32_t& min, const uint32_t& max, const uint32_t& step) override;
        void incStep() override;
        void setPos(const uint32_t& pos) override;
        void setColor(const PXColor& front, const PXColor& back) override;
};
#pragma endregion WinProgressBar

#pragma region WinCheckBox
class LIB WinCheckBox : public PXCheckBox {
    public:
        WinCheckBox(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback);
        void onClick() override;
        void setState(const bool& state) override;
        bool getState() const override;
        void toggleState() override; 
};
#pragma endregion WinComboBox

#pragma region WinRadioButton
class LIB WinRadioButton : public PXRadioButton {
    public:
        WinRadioButton(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback);
        void onClick() override;
        void setState(const bool& state) override;
        bool getState() const override;
        void toggleState() override;       
};
#pragma endregion WinRadioButton 

#pragma region WinGroupBox
class LIB WinGroupBox : public PXGroupBox {
    public:
        WinGroupBox(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback);
        // void onClick() override;        
};
#pragma endregion WinGroupBox

#pragma region WinTreeView
class LIB WinTreeView : public PXTreeView {
    public:
        WinTreeView(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback);
        void onClick() override;
        void addNode(PXNode& node, const size_t& pos) override;
        void removeNode(const size_t& pos) override;
        const PXNode* getSelectedNode() const override;
};
#pragma endregion WinTreeView

#pragma region WinStatusBar
class LIB WinStatusBar : public PXStatusBar {
    public:
        WinStatusBar(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback);
        void onClick() override;
        void addPart(const double& relEndPos, const PXString& text) override;
        void updateParts(const PXString& text=EMPTY, const size_t& idx=-1) override;
};
#pragma endregion WinStatusBar

#pragma region WinSpin
class LIB WinSpin : public PXSpin {
    public:
        WinSpin(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(const bool& up)>& callback);
        void onClick(const bool& up) override;        
};
#pragma endregion WinSpin
