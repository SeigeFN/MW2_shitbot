// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#define ProcessAddy ((DWORD_PTR)GetModuleHandle(L"iw4mp.exe"))
#define PI 3.1415926

DWORD WINAPI HackThread(HMODULE hModule)
{

    uintptr_t lclEntPtr;

    char** noRecoilFunc = (char**)(ProcessAddy + 0x79F00);
    char** noSpreadFunc = (char**)(ProcessAddy + 0x7A140);


    AllocConsole();
    FILE* dummy;
    freopen_s(&dummy, "CONOUT$", "w", stdout);

    static bool NRToggle = false;
    static bool NRSToggle = false;
    const char* NRNull = "\xC3\x90\x90";
    const char* NR_OG = "\x83\xEC\x0C";
    static bool NSToggle = false;
    const char* NSNull = "\xC3\x90\x90\x90";
    const char* NS_OG = "\x8B\x4C\x24\x04";
    DWORD oldprotect;

    while (true)
    {
        //backspace - quit
        if (GetAsyncKeyState(VK_BACK)) {
            break;
        }

        //deprecated individual no spread/recoil functions
        /*
        //L - no recoil
        if (GetAsyncKeyState(0x4C) & 1) {
            NRToggle = !NRToggle;
            if (NRToggle) {
                std::cout << "jeepnitz" << std::endl;
                VirtualProtect((LPVOID)noRecoilFunc, 3, PAGE_EXECUTE_READWRITE, &oldprotect);
                memcpy((void*)noRecoilFunc, (void*)NRNull, 3);
                VirtualProtect((LPVOID)noRecoilFunc, 3, oldprotect, &oldprotect);
            }
            if (!NRToggle) {
                std::cout << "jorpnitz" << std::endl;
                VirtualProtect((LPVOID)noRecoilFunc, 3, PAGE_EXECUTE_READWRITE, &oldprotect);
                memcpy((void*)noRecoilFunc, (void*)NR_OG, 3);
                VirtualProtect((LPVOID)noRecoilFunc, 3, oldprotect, &oldprotect);
            }
        }
        //K - no spread
        if (GetAsyncKeyState(0x4B) & 1) {
            NSToggle = !NSToggle;
            if (NSToggle) {
                std::cout << "shleepnitz" << std::endl;
                VirtualProtect((LPVOID)noSpreadFunc, 4, PAGE_EXECUTE_READWRITE, &oldprotect);
                memcpy((void*)noSpreadFunc, (void*)NSNull, 4);
                VirtualProtect((LPVOID)noSpreadFunc, 2, oldprotect, &oldprotect);
            }
            if (!NSToggle) {
                std::cout << "shlorpnitz" << std::endl;
                VirtualProtect((LPVOID)noSpreadFunc, 4, PAGE_EXECUTE_READWRITE, &oldprotect);
                memcpy((void*)noSpreadFunc, (void*)NS_OG, 4);
                VirtualProtect((LPVOID)noSpreadFunc, 4, oldprotect, &oldprotect);
            }

        }
        */

        //UP+LEFT - no spread + no recoil
        if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && (GetAsyncKeyState(VK_UP) & 1)) {
            NRSToggle = !NRSToggle;
            if (NRSToggle) {
                std::cout << "gleepnitz" << std::endl;
                VirtualProtect((LPVOID)noRecoilFunc, 3, PAGE_EXECUTE_READWRITE, &oldprotect);
                memcpy((void*)noRecoilFunc, (void*)NRNull, 3);
                VirtualProtect((LPVOID)noRecoilFunc, 3, oldprotect, &oldprotect);
                VirtualProtect((LPVOID)noSpreadFunc, 4, PAGE_EXECUTE_READWRITE, &oldprotect);
                memcpy((void*)noSpreadFunc, (void*)NSNull, 4);
                VirtualProtect((LPVOID)noSpreadFunc, 2, oldprotect, &oldprotect);
            }
            if (!NRSToggle) {
                std::cout << "glorpnitz" << std::endl;
                VirtualProtect((LPVOID)noRecoilFunc, 3, PAGE_EXECUTE_READWRITE, &oldprotect);
                memcpy((void*)noRecoilFunc, (void*)NR_OG, 3);
                VirtualProtect((LPVOID)noRecoilFunc, 3, oldprotect, &oldprotect);
                VirtualProtect((LPVOID)noSpreadFunc, 4, PAGE_EXECUTE_READWRITE, &oldprotect);
                memcpy((void*)noSpreadFunc, (void*)NS_OG, 4);
                VirtualProtect((LPVOID)noSpreadFunc, 4, oldprotect, &oldprotect);
            }

        }


    }

    fclose(stdout);
    FreeConsole();

    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
