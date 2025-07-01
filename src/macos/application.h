#pragma once

#include <MetalKit/MetalKit.hpp>
#include <CoreGraphics/CoreGraphics.h>

#include "include/application.h"
#include "include/controls.h"

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
        AppDelegate(const NS::String* title);

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
};
#pragma endregion AppDelegate

#pragma region MacOSApplication
class MacOSApplication : public PXApplication {
    public:
        MacOSApplication(const PXString& title);
        ~MacOSApplication();
        void runEventLoop() override;
        std::shared_ptr<PXControl> getMainWindow() const override;

    protected:
        std::shared_ptr<PXWindow> mainWindow;
        AppDelegate* appDelegate;
        NS::AutoreleasePool* pAutoreleasePool;
        NS::Application* pSharedApplication;
};
#pragma endregion MacOSApplication
