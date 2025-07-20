#pragma once
#import <AppKit/AppKit.h>
    
#pragma region base os local specific definitions
#define id_t(x) (reinterpret_cast<id>(x))
#define ID_t(x) (reinterpret_cast<ID>(x))
#pragma endregion base os local specific definitions

#pragma region MainView
@interface MainView : NSView
@end
#pragma endregion MainView

#pragma region AppDelegate
@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (strong, nonatomic) NSWindow *window;
@end
#pragma endregion AppDelegate
