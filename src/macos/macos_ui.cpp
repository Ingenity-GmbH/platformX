#include <MetalKit/MetalKit.hpp>

#include "../../include/ui_interface.h"

class Renderer {
    public:
        Renderer(MTL::Device* pDevice);
        ~Renderer();
        void draw(MTK::View* pView);

    private:
        MTL::Device* pDevice;
        MTL::CommandQueue* pCommandQueue;
};

Renderer::Renderer(MTL::Device* pDevice)
: pDevice(pDevice->retain()) {
    pCommandQueue = pDevice->newCommandQueue();
}

Renderer::~Renderer() {
    pCommandQueue->release();
    pDevice->release();
}

void Renderer::draw(MTK::View* pView) {
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* pCmd = pCommandQueue->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder(pRpd);
    pEnc->endEncoding();
    pCmd->presentDrawable(pView->currentDrawable());
    pCmd->commit();

    pPool->release();
}

class MTKViewDelegate : public MTK::ViewDelegate {
    public:
        MTKViewDelegate(MTL::Device* pDevice);
        virtual ~MTKViewDelegate() override;
        virtual void drawInMTKView(MTK::View* pView) override;

    private:
        Renderer* pRenderer;
};

class AppDelegate : public NS::ApplicationDelegate {
    public:
        ~AppDelegate();

        NS::Menu* createMenuBar();

        virtual void applicationWillFinishLaunching(NS::Notification* pNotification) override;
        virtual void applicationDidFinishLaunching(NS::Notification* pNotification) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* pSender) override;

    private:
        NS::Window* pWindow;
        MTK::View* pMtkView;
        MTL::Device* pDevice;
        MTKViewDelegate* pViewDelegate = nullptr;
};

AppDelegate::~AppDelegate() {
    pMtkView->release();
    pWindow->release();
    pDevice->release();
    delete pViewDelegate;
}

NS::Menu* AppDelegate::createMenuBar() {
    using NS::UTF8StringEncoding;

    NS::Menu* pMainMenu = NS::Menu::alloc()->init();
    NS::MenuItem* pAppMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu* pAppMenu = NS::Menu::alloc()->init(NS::String::string("Appname", UTF8StringEncoding));

    NS::String* appName = NS::RunningApplication::currentApplication()->localizedName();
    NS::String* quitItemName = NS::String::string("Quit ", UTF8StringEncoding)->stringByAppendingString(appName);
    SEL quitCb = NS::MenuItem::registerActionCallback("appQuit", [](void*,SEL,const NS::Object* pSender){
        auto pApp = NS::Application::sharedApplication();
        pApp->terminate(pSender);
    });

    NS::MenuItem* pAppQuitItem = pAppMenu->addItem(quitItemName, quitCb, NS::String::string("q", UTF8StringEncoding));
    pAppQuitItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);
    pAppMenuItem->setSubmenu(pAppMenu);

    NS::MenuItem* pWindowMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu* pWindowMenu = NS::Menu::alloc()->init(NS::String::string("Window", UTF8StringEncoding));

    SEL closeWindowCb = NS::MenuItem::registerActionCallback("windowClose", [](void*, SEL, const NS::Object*){
        auto pApp = NS::Application::sharedApplication();
            pApp->windows()->object< NS::Window >(0)->close();
    });
    NS::MenuItem* pCloseWindowItem = pWindowMenu->addItem(NS::String::string("Close Window", UTF8StringEncoding), closeWindowCb, NS::String::string("w", UTF8StringEncoding));
    pCloseWindowItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

    pWindowMenuItem->setSubmenu(pWindowMenu);

    pMainMenu->addItem(pAppMenuItem);
    pMainMenu->addItem(pWindowMenuItem);

    pAppMenuItem->release();
    pWindowMenuItem->release();
    pAppMenu->release();
    pWindowMenu->release();

    return pMainMenu->autorelease();
}

void AppDelegate::applicationWillFinishLaunching(NS::Notification* pNotification) {
    NS::Menu* pMenu = createMenuBar();
    NS::Application* pApp = reinterpret_cast< NS::Application* >(pNotification->object());
    pApp->setMainMenu(pMenu);
    pApp->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

void AppDelegate::applicationDidFinishLaunching(NS::Notification* pNotification) {
    CGRect frame = (CGRect){ {100.0, 100.0}, {512.0, 512.0} };

    pWindow = NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskClosable|NS::WindowStyleMaskTitled,
        NS::BackingStoreBuffered,
        false);

    pDevice = MTL::CreateSystemDefaultDevice();

    pMtkView = MTK::View::alloc()->init(frame, pDevice);
    pMtkView->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    pMtkView->setClearColor(MTL::ClearColor::Make(0.01, 0.01, 0.01, 1.0));

    pViewDelegate = new MTKViewDelegate(pDevice);
    pMtkView->setDelegate(pViewDelegate);

    pWindow->setContentView(pMtkView);
    pWindow->setTitle(NS::String::string("maindarwin", NS::StringEncoding::UTF8StringEncoding));

    pWindow->makeKeyAndOrderFront(nullptr);

    NS::Application* pApp = reinterpret_cast<NS::Application*>(pNotification->object());
    pApp->activateIgnoringOtherApps(true);
}

bool AppDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application* pSender) {
    return true;
}

MTKViewDelegate::MTKViewDelegate(MTL::Device* pDevice)
: MTK::ViewDelegate()
, pRenderer(new Renderer(pDevice)) {}

MTKViewDelegate::~MTKViewDelegate() {
    delete pRenderer;
}

void MTKViewDelegate::drawInMTKView(MTK::View* pView) {
    pRenderer->draw(pView);
}

class MacOSUI : public UIInterface {
    AppDelegate appDelegate;
    NS::AutoreleasePool* pAutoreleasePool;
    NS::Application* pSharedApplication;

    public:
        MacOSUI() : appDelegate() {}
        ~MacOSUI() {
            pSharedApplication->autorelease();
            pAutoreleasePool->release();
        }
        
        void createWindow() override {
            pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
            pSharedApplication = NS::Application::sharedApplication();
            pSharedApplication->setDelegate(&appDelegate);
            pSharedApplication->run();
        }
        
        void showMessage(const char* message) override {
            printf("Message: %s\n", message);
        }
        
        void runEventLoop() override {
            // Event loop
        }
};

UIInterface* createNativeUI() {
    return new MacOSUI();
}
