#include<Windows.h>

DWORD getProcId(const wchar_t* game);
uintptr_t getModuleBaseAdrr(DWORD procId);
uintptr_t getDMAAddy(std::vector<int> offsets, uintptr_t ptr, HANDLE procHand);

