#include "include/global.h"
#include "application.h"
#include "application.hh"

@implementation MainView
- (void)drawRect:(NSRect)dirtyRect {
    [[NSColor whiteColor] setFill];
    NSRectFill(dirtyRect);
}
@end

@implementation AppDelegate
- (NSMenu*)createMenuBar {
    NSMenu *mainMenu = [NSMenu new];
    NSMenuItem *appMenuItem = [NSMenuItem new];
    [mainMenu addItem:appMenuItem];

    NSMenu *appMenu = [NSMenu new];
    NSMenuItem *quitMenuItem = [[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(terminate:) keyEquivalent:@"q"];
    [appMenu addItem:quitMenuItem];

    [appMenuItem setSubmenu:appMenu];
    return mainMenu;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    NSRect screen = CGDisplayBounds(CGMainDisplayID());
    NSRect frame = (NSRect){{   (screen.size.width-MIN(screen.size.width,STD_MAINWIN_SIZE_WIDTH))/2.0, 
                                (screen.size.height-MIN(screen.size.height,STD_MAINWIN_SIZE_HEIGHT))/2.0},
                                {MIN(screen.size.width,STD_MAINWIN_SIZE_WIDTH), MIN(screen.size.height,STD_MAINWIN_SIZE_HEIGHT)} };

    self.window = [[NSWindow alloc] initWithContentRect:frame
                                    styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
                                    backing:NSBackingStoreBuffered
                                    defer:NO];

    [self.window setTitle:@"AppKit Demo"];
    [self.window setContentView:[[MainView alloc] initWithFrame:frame]];
    [self.window makeKeyAndOrderFront:nil];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*) sender {
    return YES;
}
@end

#pragma region macOSApplication
MacOSApplication::MacOSApplication() {
    pApp = ID_t([NSApplication sharedApplication]);
    pAppDelegate = ID_t([AppDelegate new]);

    [id_t(pApp) setDelegate: id_t(pAppDelegate)];
    [id_t(pApp) setMainMenu:[id_t(pAppDelegate) createMenuBar]];
    [id_t(pApp) setActivationPolicy:NSApplicationActivationPolicyRegular];
    [id_t(pApp) activateIgnoringOtherApps:YES];
}

MacOSApplication::~MacOSApplication() {
    [id_t(pAppDelegate) release];
    [id_t(pApp) release];
}
         
int MacOSApplication::runEventLoop() {
    [id_t(pApp) run];
    return 0;
}
#pragma endregion MacOSApplication
