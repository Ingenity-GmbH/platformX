#pragma once

#include "include/global.h"
#include <string>
#include <vector>

namespace util {
    void LIB setFont(const PXHandle& handle);
    void LIB setTitle(const PXHandle& handle, const std::string& title);
    std::string LIB getTitle(const PXHandle& handle);
    void LIB setWindowState(const PXHandle& handle, const int32_t& state);
    void LIB setState(const PXHandle& handle, const bool& state);
    bool LIB getState(const PXHandle& handle);
    void LIB toggleState(const PXHandle& handle);
    void LIB addItems(const PXHandle& handle, const std::vector<std::string>& items);
    size_t LIB getSelectedItem(const PXHandle& handle, const PXType& type);
}
    