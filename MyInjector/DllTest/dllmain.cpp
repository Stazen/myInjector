// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include <Windows.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        MessageBoxA(0, "Dll Injected", 0, 0);
    }
    return TRUE;
}

