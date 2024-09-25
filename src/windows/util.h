#pragma once

#include "include/global.h"
#include <string>
#include <vector>

namespace util {
    void setFont(const PXHandle& handle);
    void setTitle(const PXHandle& handle, const std::string& title);
    std::string getTitle(const PXHandle& handle);
    void addItems(const PXHandle& handle, const std::vector<std::string>& items);
    size_t getSelectedItem(const PXHandle& handle, const PXType& type);
}
    