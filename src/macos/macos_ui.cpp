#include "macos_ui.h"

#include "include/global.h"
#include "include/ui_interface.h"

#pragma region Renderer
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
#pragma endregion Renderer
#pragma region MTKViewDelegate
MTKViewDelegate::MTKViewDelegate(MTL::Device* pDevice)
: MTK::ViewDelegate(), pRenderer(new Renderer(pDevice)) {}

MTKViewDelegate::~MTKViewDelegate() {
    delete pRenderer;
}

void MTKViewDelegate::drawInMTKView(MTK::View* pView) {
    pRenderer->draw(pView);
}
#pragma endregion MTKViewDelegate
#pragma region AppDelegate
AppDelegate::AppDelegate(const NS::String* title, const UIInterface* interface)
: NS::ApplicationDelegate(), title(title), interface(interface) {}

NS::Menu* AppDelegate::createMenuBar() {
    using NS::UTF8StringEncoding;

    NS::String* appName = NS::RunningApplication::currentApplication()->localizedName();

    NS::Menu* pMainMenu = NS::Menu::alloc()->init();
    NS::MenuItem* pAppMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu* pAppMenu = NS::Menu::alloc()->init(appName);

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
    // NS::Menu* pMenu = createMenuBar();
    pApp = reinterpret_cast< NS::Application*>(pNotification->object());
    // pApp->setMainMenu(pMenu);
    pApp->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

 void AppDelegate::applicationWillTerminate(NS::Notification* pNotification) {
    delete pViewDelegate;
    delete interface;
    pMtkView->release();
    pWindow->release();
    pDevice->release();
 }

void AppDelegate::applicationDidFinishLaunching(NS::Notification* pNotification) {
    CGRect screen = CGDisplayBounds(CGMainDisplayID());
    CGRect frame = (CGRect){{   (screen.size.width-MIN(screen.size.width,STD_WIN_SIZE_WIDTH))/2.0, 
                                (screen.size.height-MIN(screen.size.height,STD_WIN_SIZE_HEIGHT))/2.0},
                                {MIN(screen.size.width,STD_WIN_SIZE_WIDTH), MIN(screen.size.height,STD_WIN_SIZE_HEIGHT)} };

    
    pWindow = NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskClosable | 
            NS::WindowStyleMaskTitled | 
            NS::WindowStyleMaskResizable,
        NS::BackingStoreBuffered,
        false);

    pDevice = MTL::CreateSystemDefaultDevice();

    pMtkView = MTK::View::alloc()->init(frame, pDevice);
    pMtkView->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    pMtkView->setClearColor(MTL::ClearColor::Make(0.01, 0.01, 0.01, 1.0));

    pViewDelegate = new MTKViewDelegate(pDevice);
    pMtkView->setDelegate(pViewDelegate);

    pWindow->setTitle(title);
    pWindow->setContentView(pMtkView);

    pWindow->makeKeyAndOrderFront(nullptr);

    NS::Application* pApp = reinterpret_cast<NS::Application*>(pNotification->object());
    pApp->activateIgnoringOtherApps(true);
}

bool AppDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application* pSender) {
    return true;
}
#pragma endregion AppDelegate
#pragma region MacOSUI
MacOSUI::~MacOSUI() {
    pSharedApplication->autorelease();
    pAutoreleasePool->release();
    delete appDelegate;
}
        
void MacOSUI::createWindow(const std::string& windowTitle) {
    appDelegate = new AppDelegate(NS::String::string(windowTitle.c_str(), NS::UTF8StringEncoding), this);
    pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
    pSharedApplication = NS::Application::sharedApplication();
    pSharedApplication->setDelegate(appDelegate);
}
             
void MacOSUI::runEventLoop() {
    // Event loop
    pSharedApplication->run();
}

UIInterface* createUI() {
    return new MacOSUI();
}
#pragma endregion MacOSUI