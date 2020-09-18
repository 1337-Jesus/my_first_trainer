#include<Windows.h>
#include<iostream>
#include<vector>
#include"functions.h"

int main(void) {


	const wchar_t game[14]{ L"ac_client.exe" };

	//get processID
	DWORD ProcID{ getProcId(L"ac_client.exe") };

	//get baseaddress
	uintptr_t BaseAddy{ getModuleBaseAdrr(ProcID) };


	//get gamehandle
	HANDLE hgame{ OpenProcess(PROCESS_ALL_ACCESS,0, ProcID) };

	//get finaladdy by adding offsets from vector to baseaddress
	std::vector<int> offsets{ 0x374, 0x14, 0x0 };
	uintptr_t finaladdy{ getDMAAddy(offsets, BaseAddy, hgame) };

	//write to memory
	int ammo{ 1337 };
	WriteProcessMemory(hgame, (BYTE*)finaladdy, &ammo, sizeof(ammo), 0);
}
