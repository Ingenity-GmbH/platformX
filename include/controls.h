#pragma once

#include "control.h"

#pragma region PXWindow
class LIB PXWindow : public PXControl {
    public:
        PXWindow(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, WINDOW) {}
        virtual ~PXWindow() {};
        bool hasCallback() const override { return false; }
};
using PXWindowSharedPtr = std::shared_ptr<PXWindow>;
LIB PXWindow* createMainWindow(const PXString& title);
LIB PXWindow* createWindow(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size);
LIB PXWindow* createWindow(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position);
LIB PXWindow* createWindow(const PXString& title, std::shared_ptr<PXControl> parent, const PXSize& size);
LIB PXWindow* createWindow(const PXString& title, std::shared_ptr<PXControl> parent);
#pragma endregion PXWindow

#pragma region PXButton
class LIB PXButton : public PXControl {
    public:
        PXButton(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXButton() = default;
        virtual void onClick() = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }

    protected:
        std::function<void()> callback;
};
using PXButtonSharedPtr = std::shared_ptr<PXButton>;
LIB PXButton* createButton(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback=nullptr);
LIB PXButton* createButton(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback=nullptr);
#pragma endregion PXButton

#pragma region PXEdit
class LIB PXEdit : public PXControl {
    public:
        PXEdit(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, EDIT) {}
        virtual ~PXEdit() = default;
        virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }

    protected:
        std::function<void(const uint32_t& key)> callback;
};
using PXEditSharedPtr = std::shared_ptr<PXEdit>;
LIB PXEdit* createEdit(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXEdit* createEdit(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXEdit

#pragma region PXText
class LIB PXText : public PXControl {
    public:
        PXText(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, TEXT) {}
        virtual ~PXText() = default;
        // virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }

    protected:
        std::function<void(const uint32_t& key)> callback;
};
using PXTextSharedPtr = std::shared_ptr<PXText>;
LIB PXText* createText(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXText* createText(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXText

#pragma region PXListBox
class LIB PXListBox : public PXControl {
    public:
        PXListBox(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, LISTBOX) {}
        virtual ~PXListBox() = default;
        // virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addNode(PXNode& node, const size_t& pos=UINT64_MAX) = 0;
        virtual void removeNode(const size_t& pos) = 0;
        virtual const PXNode* getSelectedNode() const = 0;

    protected:
        std::function<void(const uint32_t& key)> callback;
        std::vector<PXNode> nodes;
};
using PXListBoxSharedPtr = std::shared_ptr<PXListBox>;
LIB PXListBox* createListBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXListBox* createListBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXListBox

#pragma region PXComboBox
class LIB PXComboBox : public PXControl {
    public:
        PXComboBox(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, COMBOBOX) {}
        virtual ~PXComboBox() = default;
        // virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addNode(PXNode& node, const size_t& pos=UINT64_MAX) = 0;
        virtual void removeNode(const size_t& pos) = 0;
        virtual const PXNode* getSelectedNode() const = 0;

    protected:
        std::function<void(const uint32_t& key)> callback;
        std::vector<PXNode> nodes;
};
using PXComboBoxSharedPtr = std::shared_ptr<PXComboBox>;
LIB PXComboBox* createComboBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXComboBox* createComboBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXComboBox

#pragma region PXProgressBar
class LIB PXProgressBar : public PXControl {
    public:
        PXProgressBar(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, COMBOBOX) {}
        virtual ~PXProgressBar() = default;
        // virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void configure(const uint32_t& min, const uint32_t& max, const uint32_t& step) = 0;
        virtual void incStep() = 0;
        virtual void setPos(const uint32_t& pos) = 0;
        virtual void setColor(const PXColor& front, const PXColor& back) = 0;

    protected:
        std::function<void(const uint32_t& key)> callback; 
};
using PXProgressBarSharedPtr = std::shared_ptr<PXProgressBar>;
LIB PXProgressBar* createProgressBar(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXProgressBar* createProgressBar(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXProgressBar

#pragma region PXCheckBox
class LIB PXCheckBox : public PXControl {
    public:
        PXCheckBox(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXCheckBox() = default;
        virtual void onClick() = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void setState(const bool& state) = 0;
        virtual bool getState() const = 0;
        virtual void toggleState() = 0;

    protected:
        std::function<void(const PXHandle&)> callback;        
};
using PXCheckBoxSharedPtr = std::shared_ptr<PXCheckBox>;
LIB PXCheckBox* createCheckBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback=nullptr);
LIB PXCheckBox* createCheckBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const PXHandle& handle)>& callback=nullptr);
#pragma endregion PXCheckBox

#pragma region PXRadioButton
class LIB PXRadioButton : public PXControl {
    public:
        PXRadioButton(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXRadioButton() = default;
        virtual void onClick() = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void setState(const bool& state) = 0;
        virtual bool getState() const = 0;
        virtual void toggleState() = 0;

    protected:
        std::function<void(const PXHandle& handle)> callback;        
};
using PXRadioButtonSharedPtr = std::shared_ptr<PXRadioButton>;
LIB PXRadioButton* createRadioButton(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const PXHandle& handle)>& callback=nullptr);
LIB PXRadioButton* createRadioButton(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const PXHandle& handle)>& callback=nullptr);
#pragma endregion PXRadioButton

#pragma region PXRadioButton

#pragma region PXGroupBox
class LIB PXGroupBox : public PXControl {
    public:
        PXGroupBox(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, GROUPBOX) {}
        virtual ~PXGroupBox() = default;
        // virtual void onClick() = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        
    protected:
        std::function<void()> callback;  
};
using PXGroupBoxSharedPtr = std::shared_ptr<PXGroupBox>;
LIB PXGroupBox* createGroupBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback=nullptr);
LIB PXGroupBox* createGroupBox(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback=nullptr);
#pragma endregion PXGroupBox

#pragma region PXTreeView
class LIB PXTreeView : public PXControl {
    public:
        PXTreeView(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, TREEVIEW) {}
        virtual ~PXTreeView() = default;
        virtual void onClick() = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addNode(PXNode& node, const size_t& pos=UINT64_MAX) = 0;
        virtual void removeNode(const size_t& pos) = 0;
        virtual const PXNode* getSelectedNode() const = 0;

    protected:
        std::function<void()> callback;
        std::vector<PXNode> nodes;
        
};
using PXTreeViewSharedPtr = std::shared_ptr<PXTreeView>;
LIB PXTreeView* createTreeView(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback=nullptr);
LIB PXTreeView* createTreeView(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback=nullptr);
#pragma endregion PXTreeView

#pragma region PXStatusBar
class LIB PXStatusBar : public PXControl {
    public:
        PXStatusBar(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, STATUSBAR) {}
        virtual ~PXStatusBar() = default;
        virtual void onClick() = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addPart(const double& relEndPos, const PXString& text) = 0;
        virtual void updateParts(const PXString& text, const size_t& idx) = 0;
        
    protected:
        std::function<void()> callback;
        std::vector<PXStatusBarPart> parts;       
};
using PXStatusBarSharedPtr = std::shared_ptr<PXStatusBar>;
LIB PXStatusBar* createStatusBar(const PXString& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback=nullptr);
LIB PXStatusBar* createStatusBar(const PXString& title, std::shared_ptr<PXControl> parent, const std::function<void()>& callback=nullptr);
#pragma endregion PXStatusBar