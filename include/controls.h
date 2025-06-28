#pragma once

#include "control.h"

#pragma region PXWindow
class LIB PXWindow : public PXControl {
    public:
        PXWindow(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size) {}
        virtual ~PXWindow() {};
        bool hasCallback() const override { return false; }
};
using PXWindowSharedPtr = std::shared_ptr<PXWindow>;
LIB PXWindow* createMainWindow(const std::string& title);
LIB PXWindow* createWindow(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size);
LIB PXWindow* createWindow(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position);
LIB PXWindow* createWindow(const std::string& title, std::shared_ptr<PXControl> parent, const PXSize& size);
LIB PXWindow* createWindow(const std::string& title, std::shared_ptr<PXControl> parent);
#pragma endregion PXWindow

#pragma region PXButton
class LIB PXButton : public PXControl {
    public:
        PXButton(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXButton() = default;
        virtual void onClick() = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }

    protected:
        std::function<void()> callback;
};
using PXButtonSharedPtr = std::shared_ptr<PXButton>;
LIB PXButton* createButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback=nullptr);
LIB PXButton* createButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback=nullptr);
#pragma endregion PXButton

#pragma region PXEdit
class LIB PXEdit : public PXControl {
    public:
        PXEdit(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, EDIT) {}
        virtual ~PXEdit() = default;
        virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }

    protected:
        std::function<void(const uint32_t& key)> callback;
};
using PXEditSharedPtr = std::shared_ptr<PXEdit>;
LIB PXEdit* createEdit(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXEdit* createEdit(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXEdit

#pragma region PXText
class LIB PXText : public PXControl {
    public:
        PXText(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, TEXT) {}
        virtual ~PXText() = default;
        // virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }

    protected:
        std::function<void(const uint32_t& key)> callback;
};
using PXTextSharedPtr = std::shared_ptr<PXText>;
LIB PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXText

#pragma region PXListBox
class LIB PXListBox : public PXControl {
    public:
        PXListBox(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, LISTBOX) {}
        virtual ~PXListBox() = default;
        // virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addItem(const std::string& title, const size_t& pos=UINT64_MAX) = 0;
        virtual void removeItem(const size_t& pos) = 0;
        virtual size_t getSelectedItem() const = 0;

    protected:
        std::function<void(const uint32_t& key)> callback;
        std::vector<std::string> items;
};
using PXListBoxSharedPtr = std::shared_ptr<PXListBox>;
LIB PXListBox* createListBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXListBox* createListBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXListBox

#pragma region PXComboBox
class LIB PXComboBox : public PXControl {
    public:
        PXComboBox(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, COMBOBOX) {}
        virtual ~PXComboBox() = default;
        // virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void addItem(const std::string& title, const size_t& pos=UINT64_MAX) = 0;
        virtual void removeItem(const size_t& pos) = 0;
        virtual size_t getSelectedItem() const = 0;

    protected:
        std::function<void(const uint32_t& key)> callback;
        std::vector<std::string> items;
};
using PXComboBoxSharedPtr = std::shared_ptr<PXComboBox>;
LIB PXComboBox* createComboBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXComboBox* createComboBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXComboBox


#pragma region PXProgressBar
class LIB PXProgressBar : public PXControl {
    public:
        PXProgressBar(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, COMBOBOX) {}
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
LIB PXProgressBar* createProgressBar(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
LIB PXProgressBar* createProgressBar(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXProgressBar
