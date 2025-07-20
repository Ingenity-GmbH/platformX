 #pragma once

#include <AppKit/AppKit.h>
#include <map>
#include "include/controls.h"

#pragma region MacOSWindow
class LIB MacOSWindow : public PXWindow {
    public:
        MacOSWindow(const PXString& title, const bool& isChildWindow, const PXControlSharedPtr& parent=nullptr);
        ~MacOSWindow() override;        
        void setPosition(const PXPosition& position) override;
        PXPosition getPosition() override;
        void setSize(const PXSize& size) override;
        PXSize getSize() override;

        protected:
            static inline std::map<PXHandle, MacOSWindow*> handleMap{};
            static inline MacOSWindow* self = nullptr;
            bool isChildWindow = false;
};
#pragma endregion MacOSWindow

#pragma region MacOSMainWindow
class LIB MacOSMainWindow : public MacOSWindow {
    public:
        MacOSMainWindow(const PXString& title);
};
#pragma endregion MacOSMainWindow

#pragma region MacOSChildWindow
class LIB MacOSChildWindow : public MacOSWindow {
    public:
        MacOSChildWindow(const PXString& title, PXControlSharedPtr& parent, const PXPosition& position, const PXSize& size);
};
#pragma endregion MacOSChildWindow
