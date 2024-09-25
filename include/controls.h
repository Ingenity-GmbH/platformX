#pragma once

#include "control.h"

#pragma region PXWindow
class PXWindow : public PXControl {
    public:
        PXWindow(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size) {}
        virtual ~PXWindow() {};
        bool hasCallback() const override { return false; }
        virtual void setTitle(const std::string& title) = 0;
        virtual std::string getTitle() = 0;
};
PXWindow* createWindow(const std::string& title);
#pragma endregion PXWindow

#pragma region PXButton
class PXButton : public PXControl {
    public:
        PXButton(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, BUTTON) {}
        virtual ~PXButton() = default;
        virtual void onClick() = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void setTitle(const std::string& title) = 0;
        virtual std::string getTitle() = 0;

    protected:
        std::function<void()> callback;
};
PXButton* createButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void()>& callback=nullptr);
PXButton* createButton(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void()>& callback=nullptr);
#pragma endregion PXButton

#pragma region PXEdit
class PXEdit : public PXControl {
    public:
        PXEdit(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, EDIT) {}
        virtual ~PXEdit() = default;
        virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void setTitle(const std::string& title) = 0;
        virtual std::string getTitle() = 0;

    protected:
        std::function<void(const uint32_t& key)> callback;
};
PXEdit* createEdit(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
PXEdit* createEdit(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXEdit

#pragma region PXText
class PXText : public PXControl {
    public:
        PXText(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, TEXT) {}
        virtual ~PXText() = default;
        // virtual void onKeyPress(const uint32_t& key) = 0;
        bool hasCallback() const override { return callback == nullptr ? false : true; }
        virtual void setTitle(const std::string& title) = 0;
        virtual std::string getTitle() = 0;

    protected:
        std::function<void(const uint32_t& key)> callback;
};
PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
PXText* createText(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXText

#pragma region PXListBox
class PXListBox : public PXControl {
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
PXListBox* createListBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
PXListBox* createListBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXListBox

#pragma region PXComboBox
class PXComboBox : public PXControl {
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
PXComboBox* createComboBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
PXComboBox* createComboBox(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXComboBox


#pragma region PXProgressBar
class PXProgressBar : public PXControl {
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
PXProgressBar* createProgressBar(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const PXSize& size, const std::function<void(const uint32_t& key)>& callback=nullptr);
PXProgressBar* createProgressBar(const std::string& title, std::shared_ptr<PXControl> parent, const PXPosition& position, const std::function<void(const uint32_t& key)>& callback=nullptr);
#pragma endregion PXProgressBar
