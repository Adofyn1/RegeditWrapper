#include "RegeditWrapper.h"
#include "../lazy_importer.hpp"

#define DEBUG

#ifdef DEBUG
#define LOG(...) printf( __VA_ARGS__ )
#else
#define LOG(...)
#endif

RegeditWrapper::RegeditWrapper(HKEY key, const std::string_view subKey, DWORD options, REGSAM samDesired) : subKey_( subKey )
{
    const auto result = LI_FN( RegCreateKeyExA )( key, subKey.data(), NULL, nullptr, options, samDesired, nullptr, &key_, nullptr );

    if (result != ERROR_SUCCESS)
        LOG( "[RegeditWrapper::RegeditWrapper] Result RegOpenKeyEx: %ld\n", result );
    else
        LOG( "[RegeditWrapper::RegeditWrapper] Registry key successfully opened\n" );
}

RegeditWrapper::~RegeditWrapper()
{
    if (key_)
        LI_FN( RegCloseKey )( key_ );
    else
        LOG( "[RegeditWrapper::~RegeditWrapper] Registry key is not open\n" );
}

bool RegeditWrapper::Write(const std::string_view valueName, DWORD type, const BYTE* data, DWORD length)
{
    if (!key_)
    {
        LOG( "[RegeditWrapper::Write] Registry key is not open\n" );
        return false;
    }

    const auto result = LI_FN( RegSetValueExA )( key_, valueName.data(), NULL, type, data, length );

    if (result != ERROR_SUCCESS)
    {
        LOG( "[RegeditWrapper::Write] Failed to write value: %ld\n", result );
        return false;
    }

    return true;
}

bool RegeditWrapper::Read(const std::string_view valueName, PVOID data, DWORD size, DWORD flags)
{
    if (!key_)
    {
        LOG( "[RegeditWrapper::Read] Registry key is not open\n" );
        return false;
    }

    const auto result = LI_FN( RegGetValueA )( key_, nullptr, valueName.data(), flags, nullptr, data, &size );

    if (result != ERROR_SUCCESS)
    {
        LOG( "[RegeditWrapper::Read] Failed to read value: %ld\n", result );
        return false;
    }

    return true;
}
