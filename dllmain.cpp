#include <iostream>
#include <Windows.h>
/*class CWeapon
{
public:
	char pad_0000[8]; //0x0000
	uint32_t N0000070D; //0x0008
	uint32_t CurrentWeapon; //0x000C
	char pad_0010[8]; //0x0010
	float CrossAir; //0x0018
	char pad_001C[156]; //0x001C
	uint32_t N00000723; //0x00B8
	char pad_00BC[20]; //0x00BC
	uint32_t Grenades; //0x00D0
	char pad_00D4[3028]; //0x00D4
	char *ShaderName; //0x0CA8
	char pad_0CB0[1112]; //0x0CB0
}; //Size: 0x1108
static_assert(sizeof(CWeapon) == 0x1108);

class Player
{
public:
	char pad_0000[32]; //0x0000
	float PlayerPositionX; //0x0020
	float PlayerPositionY; //0x0024
CameraAcceleration; //0x0028
	char pad_0034[188]; //0x0034
	float CameraPitch; //0x00F0
	float CameraYaw; //0x00F4
	char pad_00F8[804]; //0x00F8
	class CWeapon m_Weapon; //0x041C
	char pad_1524[4184]; //0x1524
}; //Size: 0x257C
static_assert(sizeof(Player) == 0x257C);

class N000003F8
{
public:
	char pad_0000[6280]; //0x0000
}; //Size: 0x1888
static_assert(sizeof(N000003F8) == 0x1888);*/

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

