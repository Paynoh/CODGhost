#include <iostream>
#include <Windows.h>


using GetStringFromScriptingEnginefn = char* (__fastcall*)(const char* a1);

//using IDK = void* (__fastcall*)(__int64 a1, const char* Command); // return a pointer to a string containing the Command string //14023E100
////__int64 __fastcall C_CMD_Execute_0(int i, _BYTE* a2) // i is probably the delay?? //48 89 5c 24 ? 57 48 83 ec ? 8b f9 b9 ? ? ? ? 48 8b da e8 ? ? ? ? 0f b6 03
using C_CMD_ExecuteFN = __int64(_fastcall*)(int i, const char* Command); 
DWORD HackThread(HMODULE hModule)
{
	//GetStringFromScriptingEngine 004290E0 
	AllocConsole();
	FILE* fp{};
	freopen_s(&fp, "CONOUT$", "w", stdout);

	GetStringFromScriptingEnginefn GetStringFromScriptingEngine = reinterpret_cast<GetStringFromScriptingEnginefn>(0x14042A0E0);

	//1403B3050
	C_CMD_ExecuteFN C_CMD_Execute = reinterpret_cast<C_CMD_ExecuteFN>(0x1403B3050);
	while (!GetAsyncKeyState(VK_F8) & 1)
	{
		//std::cout << "GetStringFromScriptingEngine address: " << GetStringFromScriptingEngine << '\n';
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			std::cout << "GetStringFromScriptingEngine: " << GetStringFromScriptingEngine("mapname") << '\n';
		}
		//
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			__int64 Y = C_CMD_Execute(0, "vid_restart\n");
			std::cout << "C_CMD_Execute: called! " << Y <<'\n';
		}
		Sleep(1000);
	}
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		HANDLE A = CreateThread(NULL, 0,reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread), hModule, 0, 0);
		if (A)
			CloseHandle(A);
	}
	return TRUE;
}

