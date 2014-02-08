#include "StdAfx.h"
#include "Tool.h"

TCHAR szDllPath[DEF_BUF_SIZE] = {0};


void doListProcess()
{
	
	HANDLE hSnapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32 );


	CHAR output[1024];
	memset(output,0,1024);
	int i = 0;

	Process32First (hSnapshot, &pe32);
	do
	{
		sprintf(&output[i],"%d---%s\n",pe32.th32ProcessID,pe32.szExeFile);
		i = strlen(output);
	}while(Process32Next(hSnapshot,&pe32));
//	::AfxMessageBox(output);
	::CloseHandle(hSnapshot);
}

DWORD getDesktopHandle()
{
	HWND hwnd;
	DWORD pid;

	TCHAR output[1024];

	
	hwnd = GetDesktopWindow();
	GetWindowThreadProcessId(hwnd,&pid);

	return pid;

}


BOOL WINAPI InjectLibW(DWORD dwProcessId, PCWSTR pszLibFile) {

   BOOL bOk = FALSE; 
   HANDLE hProcess = NULL, hThread = NULL;
   PWSTR pszLibFileRemote = NULL;

   __try {
      
      hProcess = OpenProcess(
         PROCESS_QUERY_INFORMATION |   
         PROCESS_CREATE_THREAD     |   
         PROCESS_VM_OPERATION      |   
         PROCESS_VM_WRITE,             
         FALSE, dwProcessId);
      if (hProcess == NULL) __leave;

      int cch = 1 + lstrlenW(pszLibFile);
      int cb  = cch * sizeof(wchar_t);

      pszLibFileRemote = (PWSTR) 
         VirtualAllocEx(hProcess, NULL, cb, MEM_COMMIT, PAGE_READWRITE);
      if (pszLibFileRemote == NULL) __leave;

      if (!WriteProcessMemory(hProcess, pszLibFileRemote, 
         (PVOID) pszLibFile, cb, NULL)) __leave;

      PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
         GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
      if (pfnThreadRtn == NULL) __leave;

      hThread = CreateRemoteThread(hProcess, NULL, 0, 
         pfnThreadRtn, pszLibFileRemote, 0, NULL);
      if (hThread == NULL) __leave;

      WaitForSingleObject(hThread, INFINITE);

      bOk = TRUE; 
   }
   __finally { 

      if (pszLibFileRemote != NULL) 
         VirtualFreeEx(hProcess, pszLibFileRemote, 0, MEM_RELEASE);

      if (hThread  != NULL) 
         CloseHandle(hThread);

      if (hProcess != NULL) 
         CloseHandle(hProcess);
   }

   return(bOk);
}

BOOL WINAPI EjectLibW(DWORD dwProcessId, PCWSTR pszLibFile) {

   BOOL bOk = FALSE; 
   HANDLE hthSnapshot = NULL;
   HANDLE hProcess = NULL, hThread = NULL;

   __try {
     
      hthSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
      if (hthSnapshot == INVALID_HANDLE_VALUE) __leave;

      MODULEENTRY32W me = { sizeof(me) };
      BOOL bFound = FALSE;
      BOOL bMoreMods = Module32FirstW(hthSnapshot, &me);
      for (; bMoreMods; bMoreMods = Module32NextW(hthSnapshot, &me)) {
         bFound = (_wcsicmp(me.szModule,  pszLibFile) == 0) || 
                  (_wcsicmp(me.szExePath, pszLibFile) == 0);
         if (bFound) break;
      }
      if (!bFound) __leave;

      
      hProcess = OpenProcess(
         PROCESS_QUERY_INFORMATION |   
         PROCESS_CREATE_THREAD     | 
         PROCESS_VM_OPERATION,  
         FALSE, dwProcessId);
      if (hProcess == NULL) __leave;

      PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
         GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "FreeLibrary");
      if (pfnThreadRtn == NULL) __leave;

      hThread = CreateRemoteThread(hProcess, NULL, 0, 
         pfnThreadRtn, me.modBaseAddr, 0, NULL);
      if (hThread == NULL) __leave;

      WaitForSingleObject(hThread, INFINITE);

      bOk = TRUE;
   }
   __finally {

      if (hthSnapshot != NULL) 
         CloseHandle(hthSnapshot);

      if (hThread     != NULL) 
         CloseHandle(hThread);

      if (hProcess    != NULL) 
         CloseHandle(hProcess);
   }

   return(bOk);
}

