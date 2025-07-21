#pragma once
#import <AppKit/AppKit.h>

#pragma region base os local specific definitions
#define id_t(x) (reinterpret_cast<id>(x))
#define ID_t(x) (reinterpret_cast<PXHandle>(x))

@interface Selector : NSObject
@property (nonatomic, assign) PXControl* control;
@property (nonatomic, assign) void* arg;
- (void)selectorCallback:(id)sender;
@end
#pragma endregion base os local specific definitions
