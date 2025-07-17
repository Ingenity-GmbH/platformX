#include "include/util.h"

void util::setFont(const PXHandle& handle) {
}
void util::setTitle(const PXHandle& handle, const PXString& title) {
}

PXString util::getTitle(const PXHandle& handle) {
}

void util::setWindowState(const PXHandle& handle, const int32_t& state) {
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
