#pragma once

#include <MetalKit/MetalKit.hpp>
#include <CoreGraphics/CoreGraphics.h>

#include "include/ui_interface.h"

#pragma region Renderer
class Renderer {
    public:
        Renderer(MTL::Device* pDevice);
        ~Renderer();
        void draw(MTK::View* pView);

    private:
        MTL::Device* pDevice;
        MTL::CommandQueue* pCommandQueue;
};
#pragma endregion Renderer
#pragma region MTKViewDelegate
class MTKViewDelegate : public MTK::ViewDelegate {
    public:
        MTKViewDelegate(MTL::Device* pDevice);
        virtual ~MTKViewDelegate() override;
        virtual void drawInMTKView(MTK::View* pView) override;

    private:
        Renderer* pRenderer;
};
#pragma endregion MTKViewDelegate
#pragma region AppDelegate
class AppDelegate : public NS::ApplicationDelegate {
    public:
        AppDelegate(const NS::String* title, const UIInterface* interface);

        NS::Menu* createMenuBar();

        virtual void applicationWillFinishLaunching(NS::Notification* pNotification) override;
        virtual void applicationDidFinishLaunching(NS::Notification* pNotification) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* pSender) override;
        virtual void applicationWillTerminate(NS::Notification* pNotification) override;

    private:
        NS::Application* pApp = nullptr;
        MTK::View* pMtkView = nullptr;
        MTL::Device* pDevice = nullptr;
        MTKViewDelegate* pViewDelegate = nullptr;
        NS::Window* pWindow = nullptr;

        const NS::String* title = nullptr;
        const UIInterface* interface = nullptr;
};
#pragma endregion AppDelegate
#pragma region MacOSUI
class MacOSUI : public UIInterface {
    public:
        ~MacOSUI();
        void createWindow(const std::string& windowTitle) override;
        void runEventLoop() override ;

    private:
        AppDelegate* appDelegate;
        NS::AutoreleasePool* pAutoreleasePool;
        NS::Application* pSharedApplication;
};

UIInterface* createUI();
#pragma endregion MacOSUI
