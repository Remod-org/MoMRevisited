// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MinHook.h"
#include <thread>

#ifdef __linux__ 
// Note that linux is not yet working
int approve_offset = 0x00962ca8;
#elif _WIN32
int approve_offset = 0x880050;
#else

#endif

void* origApproveLogin = nullptr;

unsigned long ApproveLoginHook(void* param1, unsigned long* param_2, unsigned int* param_3){
  return 0x10101010;
}

bool oldApproveLoginHook(void* param1, void* param2, void* param_3){
	return true;
}

void InitHooking() {
	uintptr_t baseaddress = (uintptr_t)GetModuleHandleA("MemoriesOfMarsServer.exe");

	MH_Initialize();

	LPVOID approveLogin = (LPVOID)(baseaddress + approve_offset);

	MH_CreateHook(approveLogin, ApproveLoginHook, &origApproveLogin);

	MH_EnableHook(approveLogin);
}

void ServerPatchMainThread() {
	InitHooking();
}

BOOL APIENTRY DllMain( HMODULE hModule,
		DWORD  ul_reason_for_call,
		LPVOID lpReservedB
		){

	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		std::thread t(ServerPatchMainThread);

		t.detach();
	}

	return TRUE;
}
