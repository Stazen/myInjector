#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>

using namespace std;



DWORD GetProcId(const char* pn, unsigned short int fi = 0b1101)
{
	DWORD procId = 0;
	HANDLE Hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Hsnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pE;
		pE.dwSize = sizeof(pE);

		if (Process32First(Hsnap, &pE))
		{
			if (!pE.th32ProcessID)
			{
				Process32Next(Hsnap, &pE);

			}
		}
	}
}


/*
bool InjectDynamicLibrary(DWORD processId, char* dllPath)
{
	HANDLE hTargerProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);
	
	if (hTargerProcess)
	{
		LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
		LPVOID LoadPath = VirtualAllocEx(hTargerProcess, 0, strlen(dllPath), 
			MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		HANDLE RemoteThread = CreateRemoteThread(hTargerProcess, 0, 0, 
			(LPTHREAD_START_ROUTINE)LoadLibAddr, LoadPath, 0, 0);

		WaitForSingleObject(RemoteThread, INFINITE);

		VirtualFreeEx(hTargerProcess, LoadPath, strlen(dllPath), MEM_RELEASE);
		CloseHandle(RemoteThread);
		CloseHandle(hTargerProcess);
		return true;
	}
	return false;
}*/

DWORD FindProcessId(const char *processName)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 pe;
	int pid = 0;
	BOOL hResult;

	cout << "Injector Statut : Search Process id..\n";
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (INVALID_HANDLE_VALUE == hSnapshot)
	{
		return 0;
	}

	pe.dwSize = sizeof(PROCESSENTRY32);

	hResult = Process32First(hSnapshot, &pe);

	
	while (hResult)
	{

		if (strcmp(processName, (char*)pe.szExeFile) == 0) {
			pid = pe.th32ProcessID;
			cout << "Injector Statut : Process Id found..\n";
			break;
		}

		hResult = Process32Next(hSnapshot, &pe);
	}

	CloseHandle(hSnapshot);
	cout << "Injector Statut : Returning process id.. : \n" << pid;
	return DWORD(pid);
}

int main()
{
	cout << "Injector made by Stazen\n";
	//InjectDynamicLibrary(FindProcessId("fdf.exe"), "DllTest.dll");
	FindProcessId("CalculatorApp.exe");
}