// Author: Adofyn
// Created: 21.03.2025 04:03

#pragma once
#include <string_view>
#include <Windows.h>

class RegeditWrapper
{
private:
    HKEY key_;
    std::string_view subKey_;

public:
    RegeditWrapper(HKEY key, std::string_view subKey, DWORD options = REG_OPTION_NON_VOLATILE, REGSAM samDesired = KEY_ALL_ACCESS);
    ~RegeditWrapper();

    RegeditWrapper(const RegeditWrapper&) = delete;
    RegeditWrapper& operator=(const RegeditWrapper&) = delete;

    bool Write(std::string_view valueName, DWORD type, const BYTE* data, DWORD length);
    bool Read(std::string_view valueName, PVOID data, DWORD size, DWORD flags = RRF_RT_ANY);
};
