#pragma once

#include "include/global.h"
#include "include/control.h"
#include <vector>

namespace util {
    void LIB setFont(const PXHandle& handle);
    void LIB setTitle(const PXHandle& handle, const PXString& title);
    PXString LIB getTitle(const PXHandle& handle);
    void LIB setWindowState(const PXHandle& handle, const int32_t& state);
    void LIB setState(const PXHandle& handle, const bool& state);
    bool LIB getState(const PXHandle& handle);
    void LIB toggleState(const PXHandle& handle);
    void LIB addNodes(const PXHandle& handle, std::vector<PXNode>& nodes, const PXType& type);
    size_t LIB getSelectedNode(const PXHandle& handle, const PXType& type);
    void LIB addPart(PXControl& self, std::vector<PXStatusBarPart>& parts, const double& relEndPos, const PXString& text);
    void LIB updateParts(PXControl& self, std::vector<PXStatusBarPart>& parts);
}
