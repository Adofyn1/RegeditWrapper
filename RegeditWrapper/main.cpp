#include <iostream>
#include <string>

#include "RegeditWrapper/RegeditWrapper.h"

int main()
{
    RegeditWrapper regedit{ HKEY_LOCAL_MACHINE, "SOFTWARE\\test" };

    const std::string login = "test";
    regedit.Write( "Login", REG_SZ, (BYTE*)login.c_str(), static_cast<DWORD>(login.size()) );

    /*char login[128];
    regedit.Read( "Login", login, sizeof(login) );
    std::cout << login << '\n';*/

    return 0;
}
