// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MinHook.h"
#include <thread>

void* origApproveLogin = nullptr;

bool ApproveLoginHook(void* param1, void* param2, void* param_3){
	return true;
}

void InitHooking() {
	uintptr_t baseaddress = (uintptr_t)GetModuleHandleA("MemoriesOfMarsServer.exe");

	MH_Initialize();

	LPVOID approveLogin = (LPVOID)(baseaddress + 0x880050);

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
