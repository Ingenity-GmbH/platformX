#include "include/util.h"
#include "defines.hh"

void util::setFont(const PXHandle& handle) {
}
void util::setTitle(const PXHandle& handle, const PXString& title) {
}

PXString util::getTitle(const PXHandle& handle) {
}

void util::setWindowState(const PXHandle& handle, const int32_t& state) {
}

void util::setSizePosition(const PXHandle& handle, const PXSize& size, const PXPosition& position) {
    NSRect frame = NSMakeRect(static_cast<CGFloat>(position.x), static_cast<CGFloat>(position.y), static_cast<CGFloat>(size.width), static_cast<CGFloat>(size.height));
    [reinterpret_cast<NSWindow*>(id_t(handle)) setFrame:frame display:YES];
}

void util::setState(const PXHandle& handle, const bool& state) {
}

bool util::getState(const PXHandle& handle) {
}

void LIB util::toggleState(const PXHandle& handle) {
}

void local_addNode(const PXHandle& handle, PXNode& node) {
}

void util::addNodes(const PXHandle& handle, std::vector<PXNode>& nodes, const PXType& type) {
}

size_t util::getSelectedNode(const PXHandle& handle, const PXType& type) {
}

void util::addPart(PXControl& self, std::vector<PXStatusBarPart>& parts, const double& relEndPos, const PXString& text) {
}

void util::updateParts(PXControl& self, std::vector<PXStatusBarPart>& parts) {
}
