#pragma once

#include "component.h"

#pragma region PXWindow
class PXWindow : public PXComponent {
    public:
        PXWindow(const std::string& title, const PXSize& size, const PXPosition& position) : PXComponent(title, size, position) {}
        virtual ~PXWindow() = default;
};
PXWindow* createWindow(const std::string& title);
#pragma endregion PXWindow

#pragma region PXButton
class PXButton : public PXComponent {
    public:
        PXButton(const std::string& title, const PXSize& size, const PXPosition& position) : PXComponent(title, size, position, BUTTON) {}
        virtual ~PXButton() = default;
        virtual void onClick() = 0;

    protected:
        std::function<void()> callback;
};
PXButton* createButton(const std::string& title, const PXPosition& position, std::shared_ptr<PXComponent> parent, const std::function<void()>& callback);
#pragma endregion PXButton
