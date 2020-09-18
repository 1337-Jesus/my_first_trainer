#include<Windows.h>
#include<tlhelp32.h>
#include<iostream>
#include<vector>

DWORD getProcId(const wchar_t* game)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap != INVALID_HANDLE_VALUE)
	{
		DWORD procID{ 0 };
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hProcessSnap, &pe32))
		{
			do
			{
				if (!_wcsicmp(pe32.szExeFile, game))
				{
					procID = pe32.th32ProcessID;
					break;
				}


			} while (Process32Next(hProcessSnap, &pe32));
		}
		else
			std::cout << "Process ID cant be found\n";
		CloseHandle(hProcessSnap);
		return procID;
	}
}
	uintptr_t getModuleBaseAdrr(DWORD procId)
	{
		HANDLE hmoduleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE || TH32CS_SNAPMODULE32, procId);
		uintptr_t baseAddr{ 0 };
		MODULEENTRY32 me32;
		me32.dwSize = sizeof(me32);
		if (Module32First(hmoduleSnap, &me32))
		{
			do
			{
				if (me32.th32ProcessID == procId)
				{
					baseAddr = (uintptr_t)me32.modBaseAddr;
					break;
				}

			} while (Module32Next(hmoduleSnap, &me32));
		}
		else
			std::cout << "Process ID cant be found\n";
		CloseHandle(hmoduleSnap);
		return baseAddr;
	}


	uintptr_t getDMAAddy(std::vector<int> offsets, uintptr_t ptr, HANDLE procHand)
	{
		uintptr_t addy = ptr;
		SIZE_T buffsize = offsets.size();
		for (int i{ 0 }; i < buffsize; ++i)
		{
			ReadProcessMemory(procHand, (LPCVOID)addy, (LPVOID)&addy, sizeof(addy), 0);
			addy = addy + offsets[i];
		}
		return addy;
	}