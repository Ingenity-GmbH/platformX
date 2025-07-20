
#include "include/global.h"
#include "include/util.h"
// #include "../controls.h"
#include "../window.h"
#include "window.hh"

#pragma region MacOSWindow
@implementation View
- (void)drawRect:(NSRect)rect {
    [[NSColor whiteColor] setFill];
    NSRectFill(rect);
}
@end

MacOSWindow::MacOSWindow(const PXString& title, const bool& isChildWindow, const PXControlSharedPtr& parent) 
: PXWindow(title,
    PXPosition(static_cast<uint32_t>((CGDisplayBounds(CGMainDisplayID()).size.width-std::min<uint32_t>(static_cast<uint32_t>(CGDisplayBounds(CGMainDisplayID()).size.width), STD_MAINWIN_SIZE_WIDTH)) / 2),
        static_cast<uint32_t>((CGDisplayBounds(CGMainDisplayID()).size.height-std::min<uint32_t>(static_cast<uint32_t>(CGDisplayBounds(CGMainDisplayID()).size.height), STD_MAINWIN_SIZE_HEIGHT)) / 2)),
    PXSize(std::min<uint32_t>(static_cast<uint32_t>(CGDisplayBounds(CGMainDisplayID()).size.width), STD_MAINWIN_SIZE_WIDTH),
        std::min<uint32_t>(static_cast<uint32_t>(CGDisplayBounds(CGMainDisplayID()).size.height), STD_MAINWIN_SIZE_HEIGHT))) {

    this->isChildWindow = isChildWindow;
    this->parent = parent.get();
    self = this;

    PXPosition position = getPosition();
    PXSize size = getSize();
    NSRect frame = (NSRect) {{
                                static_cast<CGFloat>(position.x), 
                                static_cast<CGFloat>(position.y), 
                            }, {   
                                static_cast<CGFloat>(size.width),
                                static_cast<CGFloat>(size.height)
                            }};

    handle = ID_t([[NSWindow alloc] initWithContentRect:frame
                                    styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
                                    backing:NSBackingStoreBuffered
                                    defer:NO]);

    [id_t(handle) setTitle:[NSString stringWithUTF8String:title.toUTF8()]];
    [id_t(handle) setContentView:[[View alloc] initWithFrame:frame]];
    [id_t(handle) makeKeyAndOrderFront:nil];

    if (isChildWindow) {
        [id_t(parent->getHandle()) addChildWindow:id_t(handle) ordered:NSWindowAbove];
        // [id_t(handle) orderOut:nil];
    }

    MacOSWindow::handleMap.insert({handle, self});
    util::setFont(handle);
}

MacOSWindow::~MacOSWindow() {
    [id_t(handle) release];
}
#pragma endregion MacOSWindow
