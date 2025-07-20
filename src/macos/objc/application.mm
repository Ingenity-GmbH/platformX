#include "include/global.h"
#include "../application.h"
#include "application.hh"

#pragma region macOSApplication
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

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*) sender {
    return YES;
}
@end

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
