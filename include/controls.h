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
LIB PXWindowSharedPtr createMainWindow(const PXString& title);
LIB PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size);
LIB PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXPosition& position);
LIB PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent, const PXSize& size);
LIB PXWindowSharedPtr createWindow(const PXString& title, PXControlSharedPtr parent);
#pragma endregion PXWindow

#pragma region PXButton
class LIB PXButton : public PXControl {
    public:
        PXButton(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXButton() {};
        bool hasCallback() const override { return callback == nullptr ? false : true; }
};
using PXButtonSharedPtr = std::shared_ptr<PXButton>;
LIB PXButtonSharedPtr createButton(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXButtonSharedPtr createButton(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXButton

#pragma region PXEdit
class LIB PXEdit : public PXControl {
    public:
        PXEdit(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, EDIT) {}
        virtual ~PXEdit() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
};
using PXEditSharedPtr = std::shared_ptr<PXEdit>;
LIB PXEditSharedPtr createEdit(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXEditSharedPtr createEdit(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXEdit

#pragma region PXText
class LIB PXText : public PXControl {
    public:
        PXText(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, TEXT) {}
        virtual ~PXText() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
};
using PXTextSharedPtr = std::shared_ptr<PXText>;
LIB PXTextSharedPtr createText(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXTextSharedPtr createText(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXText

#pragma region PXListBox
class LIB PXListBox : public PXControl {
    public:
        PXListBox(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, LISTBOX) {}
        virtual ~PXListBox() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addNode(PXNode& node, const size_t& pos=UINT64_MAX) = 0;
        virtual void removeNode(const size_t& pos) = 0;
        virtual const PXNode* getSelectedNode() const = 0;

    protected:
        std::vector<PXNode> nodes;
};
using PXListBoxSharedPtr = std::shared_ptr<PXListBox>;
LIB PXListBoxSharedPtr createListBox(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXListBoxSharedPtr createListBox(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXListBox

#pragma region PXComboBox
class LIB PXComboBox : public PXControl {
    public:
        PXComboBox(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, COMBOBOX) {}
        virtual ~PXComboBox() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addNode(PXNode& node, const size_t& pos=UINT64_MAX) = 0;
        virtual void removeNode(const size_t& pos) = 0;
        virtual const PXNode* getSelectedNode() const = 0;

    protected:
        std::vector<PXNode> nodes;
};
using PXComboBoxSharedPtr = std::shared_ptr<PXComboBox>;
LIB PXComboBoxSharedPtr createComboBox(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXComboBoxSharedPtr createComboBox(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXComboBox

#pragma region PXProgressBar
class LIB PXProgressBar : public PXControl {
    public:
        PXProgressBar(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, COMBOBOX) {}
        virtual ~PXProgressBar() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void configure(const uint32_t& min, const uint32_t& max, const uint32_t& step) = 0;
        virtual void incStep() = 0;
        virtual void setPos(const uint32_t& pos) = 0;
        virtual void setColor(const PXColor& front, const PXColor& back) = 0;
};
using PXProgressBarSharedPtr = std::shared_ptr<PXProgressBar>;
LIB PXProgressBarSharedPtr createProgressBar(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXProgressBarSharedPtr createProgressBar(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXProgressBar

#pragma region PXCheckBox
class LIB PXCheckBox : public PXControl {
    public:
        PXCheckBox(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXCheckBox() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void setState(const bool& state) = 0;
        virtual bool getState() const = 0;
        virtual void toggleState(void*) = 0;    
};
using PXCheckBoxSharedPtr = std::shared_ptr<PXCheckBox>;
LIB PXCheckBoxSharedPtr createCheckBox(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXCheckBoxSharedPtr createCheckBox(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXCheckBox

#pragma region PXRadioButton
class LIB PXRadioButton : public PXControl {
    public:
        PXRadioButton(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXRadioButton() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void setState(const bool& state) = 0;
        virtual bool getState() const = 0;
        virtual void toggleState(void*) = 0;      
};
using PXRadioButtonSharedPtr = std::shared_ptr<PXRadioButton>;
LIB PXRadioButtonSharedPtr createRadioButton(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXRadioButtonSharedPtr createRadioButton(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXRadioButton

#pragma region PXRadioButton

#pragma region PXGroupBox
class LIB PXGroupBox : public PXControl {
    public:
        PXGroupBox(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, GROUPBOX) {}
        virtual ~PXGroupBox() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
};
using PXGroupBoxSharedPtr = std::shared_ptr<PXGroupBox>;
LIB PXGroupBoxSharedPtr createGroupBox(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXGroupBoxSharedPtr createGroupBox(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXGroupBox

#pragma region PXTreeView
class LIB PXTreeView : public PXControl {
    public:
        PXTreeView(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, TREEVIEW) {}
        virtual ~PXTreeView() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addNode(PXNode& node, const size_t& pos=UINT64_MAX) = 0;
        virtual void removeNode(const size_t& pos) = 0;
        virtual const PXNode* getSelectedNode() const = 0;

    protected:
        std::vector<PXNode> nodes;
        
};
using PXTreeViewSharedPtr = std::shared_ptr<PXTreeView>;
LIB PXTreeViewSharedPtr createTreeView(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXTreeViewSharedPtr createTreeView(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXTreeView

#pragma region PXStatusBar
class LIB PXStatusBar : public PXControl {
    public:
        PXStatusBar(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, STATUSBAR) {}
        virtual ~PXStatusBar() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addPart(const double& relEndPos, const PXString& text) = 0;
        virtual void updateParts(const PXString& text, const size_t& idx) = 0;
        
    protected:
        std::vector<PXStatusBarPart> parts;       
};
using PXStatusBarSharedPtr = std::shared_ptr<PXStatusBar>;
LIB PXStatusBarSharedPtr createStatusBar(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXStatusBarSharedPtr createStatusBar(const PXString& title, PXControlSharedPtr parent, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXStatusBar

#pragma region PXSpin
class LIB PXSpin : public PXControl {
    public:
        PXSpin(const PXString& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXSpin() {}
        bool hasCallback() const override { return callback == nullptr ? false : true; }     
};
using PXSpinSharedPtr = std::shared_ptr<PXSpin>;
LIB PXSpinSharedPtr createSpin(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback=nullptr);
LIB PXSpinSharedPtr createSpin(const PXString& title, PXControlSharedPtr parent, const PXPosition& position, const std::function<void(void*)>& callback=nullptr);
#pragma endregion PXSpin
