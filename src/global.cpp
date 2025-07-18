
#include "include/global.h"

#pragma region PXString
PXString::PXString() {};
PXString::PXString(const std::string& str) : str(str) { cast(); };
PXString::PXString(const std::wstring& wstr) : wstr(wstr)  { cast();};
PXString::PXString(UTF8_t str) : str(str) { cast(); };
PXString::PXString(Unicode_t wstr) : wstr(wstr) { cast(); };

void PXString::cast() {
    if (!str.empty()) {
        std::wstring w(str.begin(), str.end());
        wstr = w;
    }
    else if (!wstr.empty()) {
        std::string s(wstr.begin(), wstr.end());
        str = s;
    }
}

std::wstring PXString::toWstring() const {
    return wstr;
}

std::string PXString::toString() const {
    return str;
}

UTF8_t PXString::toUTF8() const {
    return str.c_str();
}

Unicode_t PXString::toUnicode() const {
    return wstr.c_str();
}

PXString& PXString::operator=(const PXString& other) {
        if (this == &other) return *this;
        str = other.str;
        wstr = other.wstr;
        return *this;
}

PXString operator+(const PXString& lhs, const PXString& rhs) {
    return PXString(lhs.wstr + rhs.wstr);
}
#pragma endregion PXString

#pragma region PXPosition
PXPosition::PXPosition(uint32_t x, uint32_t y) : x(x), y(y) {}

PXPosition& PXPosition::operator+=(const PXPosition& other) {
    x += other.x;
    y += other.y;
    return *this;
}
#pragma endregion PXPosition
