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
        PXText(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, EDIT) {}
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
        PXListBox(const std::string& title, const PXPosition& position, const PXSize& size) : PXControl(title, position, size, EDIT) {}
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
