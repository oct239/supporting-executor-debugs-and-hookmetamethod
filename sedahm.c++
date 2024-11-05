#include <Windows.h>
#include <string>
#include <memory>
#include <vector>

namespace debuglibs {
    struct DebugFunctions {
        void* getupvalue;
        void* getupvalues;
        void* setconstant;
        void* setstack;
        void* setupvalue;
        void* hookmetamethod;
    };

    DWORD WINAPI SetupDebugFunctions(LPVOID) {
        HMODULE robloxModule = GetModuleHandleW(L"RobloxPlayerBeta.exe");
        if (!robloxModule) return 0;

        DebugFunctions dbg;
        dbg.getupvalue = GetProcAddress(robloxModule, "lua_getupvalue");
        dbg.getupvalues = GetProcAddress(robloxModule, "lua_getupvalues");
        dbg.setconstant = GetProcAddress(robloxModule, "lua_setconstant");
        dbg.setstack = GetProcAddress(robloxModule, "lua_setstack");
        dbg.setupvalue = GetProcAddress(robloxModule, "lua_setupvalue");
        dbg.hookmetamethod = GetProcAddress(robloxModule, "lua_hookmetamethod");

        DWORD oldProtect;
        VirtualProtect((LPVOID)robloxModule, 0x1000, PAGE_EXECUTE_READWRITE, &oldProtect);

        memcpy((void*)((uintptr_t)robloxModule + 0x1000), &dbg, sizeof(DebugFunctions));

        VirtualProtect((LPVOID)robloxModule, 0x1000, oldProtect, &oldProtect);
        
        return 0;
    }

    BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
        if (reason == DLL_PROCESS_ATTACH) {
            DisableThreadLibraryCalls(hModule);
            CreateThread(0, 0, SetupDebugFunctions, 0, 0, 0);
        }
        return TRUE;
    }
}
