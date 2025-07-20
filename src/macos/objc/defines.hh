#pragma once
#import <AppKit/AppKit.h>

#pragma region base os local specific definitions
#define id_t(x) (reinterpret_cast<id>(x))
#define ID_t(x) (reinterpret_cast<PXHandle>(x))
#pragma endregion base os local specific definitions
