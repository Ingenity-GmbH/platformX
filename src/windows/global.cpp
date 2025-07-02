
#include "include/global.h"

#pragma region PXString
PXString::PXString() : wstr(castToWstring()) {};
PXString::PXString(const std::string& str) : str(str), wstr(castToWstring())  {};
PXString::PXString(const std::wstring& wstr) : wstr(wstr)  { str = castToString(); };
PXString::PXString(const char* str) : str(str), wstr(castToWstring()) {};
PXString::PXString(const wchar_t* wstr) : wstr(wstr) { str = castToString(); };

std::wstring PXString::castToWstring() const {
    if (str.empty()) return std::wstring();
    int strLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
    std::wstring wstr(strLen, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstr[0], strLen);
    return wstr;
}

std::string PXString::castToString() const {
    if (wstr.empty()) return std::string();
    int strLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string str(strLen, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &str[0], strLen, NULL, NULL);
    return str;
}

std::wstring PXString::toWstring() const {
    return wstr;
}

std::string PXString::toString() const {
    return str;
}

LPCWSTR PXString::toLPCWSTR() const {
    return wstr.c_str();
}

LPCSTR PXString::toLPCSTR() const {
    return str.c_str();
}

PXString operator+(const PXString& lhs, const PXString& rhs) {
    return PXString(lhs.str + rhs.str);
}
#pragma endregion PXString
