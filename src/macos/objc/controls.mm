#include "include/global.h"
#include "include/util.h"
#include "defines.hh"
#include "../controls.h"

#pragma region MacOSButton
@implementation Selector
- (void)selectorCallback:(id)sender {
    _control->callback(_arg);
}
@end

MacOSButton::MacOSButton(const PXString& title, PXControl& parent, const PXPosition& position, const PXSize& size, const std::function<void(void*)>& callback) 
: PXButton(title, position, size) {
    auto parentHandle = parent.getHandle();
    this->parent = &parent;
    this->callback = callback;

    NSRect frame = (NSRect) {{
                                static_cast<CGFloat>(position.x), 
                                static_cast<CGFloat>(parent.getSize().height-position.y), 
                            }, {   
                                static_cast<CGFloat>(size.width),
                                static_cast<CGFloat>(size.height)
                            }};

    selector = ID_t([Selector new]);
    [id_t(selector) setControl:this];
    // [id_t(selector) setArg:reinterpret_cast<void*>(SOMETHING)];

    handle = ID_t([[NSButton alloc] initWithFrame:frame]);
    [id_t(handle) setTarget:id_t(selector)];
    [id_t(handle) setAction:@selector(selectorCallback:)];
    [id_t(handle) setTitle:[NSString stringWithUTF8String:title.toUTF8()]];
    
    [[id_t(parentHandle) contentView] addSubview:id_t(handle)];
    
    util::setFont(handle);
}

MacOSButton::~MacOSButton() {
    [id_t(selector) release];
    [id_t(handle) release];
}
#pragma region MacOSButton
