#include "StdAfx.h"
#include <stdlib.h>
#include "Hooker.h"

BOOL (__stdcall * Real_TextOutA)(HDC ,int ,int ,LPCSTR ,int ) = TextOutA;
BOOL (__stdcall * Real_TextOutW)(HDC ,int ,int ,LPCWSTR ,int ) = TextOutW;
BOOL (__stdcall * Real_ExtTextOutA)(HDC ,int ,int ,UINT ,CONST RECT * ,LPCSTR ,UINT ,CONST INT *) = ExtTextOutA;
BOOL (__stdcall * Real_ExtTextOutW)(HDC ,int ,int ,UINT ,CONST RECT * ,LPCWSTR ,UINT ,CONST INT *) = ExtTextOutW;



Hooker::Hooker():m_hPipe(INVALID_HANDLE_VALUE)
{
	try
	{
		m_hPipe = CreateFile(PIPE_NAME, GENERIC_READ | GENERIC_WRITE,   
			0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 

		if(m_hPipe == INVALID_HANDLE_VALUE)
			throw ;

		return ;
	}
	catch(void)
	{
		if(m_hPipe != INVALID_HANDLE_VALUE)
			CloseHandle(m_hPipe);
	}
}

void Hooker::Hook()
{
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	
	
	DetourAttach(&(PVOID&)Real_TextOutA,Fake_TextOutA);
	DetourAttach(&(PVOID&)Real_TextOutW,Fake_TextOutW);
	DetourAttach(&(PVOID&)Real_ExtTextOutA,Fake_ExtTextOutA);
	DetourAttach(&(PVOID&)Real_ExtTextOutW,Fake_ExtTextOutW);	
	
	DetourTransactionCommit();
}

void Hooker::Unhook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

	DetourDetach(&(PVOID&)Real_TextOutA,Fake_TextOutA);
	DetourDetach(&(PVOID&)Real_TextOutW,Fake_TextOutW);
	DetourDetach(&(PVOID&)Real_ExtTextOutA,Fake_ExtTextOutA);
	DetourDetach(&(PVOID&)Real_ExtTextOutW,Fake_ExtTextOutW);

    DetourTransactionCommit();
}

Hooker::~Hooker()
{

	if(m_hPipe != INVALID_HANDLE_VALUE)
		CloseHandle(m_hPipe);
}

void Hooker::communicationWithServerA(CHAR * info,UINT size,UINT fuOptions)
{
	if ( fuOptions & ETO_GLYPH_INDEX)
	{

	}
	else
	{
		WCHAR buffer[MAX_SIZE] = {0};
		UINT buffer_size = mbstowcs(buffer,info,size);
		
		communicationWithServerW(buffer,buffer_size*2,fuOptions);
	}
}

void Hooker::communicationWithServerW(WCHAR * info,UINT size,UINT fuOptions)
{
	ULONG writeNum = 0;

	if(fuOptions & ETO_GLYPH_INDEX )
	{
	
	}
	else
	{

		if(WriteFile(m_hPipe, info, size*2, &writeNum, NULL) == FALSE)  
		{
			MessageBox(0,"SendMessageError","Error",0);
		}
	}
}


Hooker * Hooker::getInstance()
{
	static Hooker * hk = new Hooker;
	return hk;
}

BOOL __stdcall Fake_TextOutA(HDC hdc,int nXStart,int nYStart,LPCSTR lpString,int cbString)
{
	Hooker * hk = Hooker::getInstance();
	hk->communicationWithServerA((CHAR *)lpString,cbString,NULL);
	return Real_TextOutA(hdc,nXStart,nYStart,lpString,cbString);
}

BOOL __stdcall Fake_TextOutW(HDC hdc,int nXStart,int nYStart,LPCWSTR lpString,int cbString)
{
	Hooker * hk = Hooker::getInstance();
	hk->communicationWithServerW((WCHAR *)lpString,cbString,NULL);
	return Real_TextOutW(hdc,nXStart,nYStart,lpString,cbString);
}

BOOL __stdcall Fake_ExtTextOutA(HDC hdc,int X,int Y,UINT fuOptions,CONST RECT * lprc,LPCSTR lpString,UINT cbCount,CONST INT * lpDx)
{
	Hooker * hk = Hooker::getInstance();
	hk->communicationWithServerA((CHAR *)lpString,cbCount,fuOptions);
	return Real_ExtTextOutA(hdc,X,Y,fuOptions,lprc,lpString,cbCount,lpDx);
}

BOOL __stdcall Fake_ExtTextOutW(HDC hdc,int X,int Y,UINT fuOptions,CONST RECT * lprc,LPCWSTR lpString,UINT cbCount,CONST INT * lpDx)
{
	Hooker * hk = Hooker::getInstance();
	hk->communicationWithServerW((WCHAR *)lpString,cbCount,fuOptions);
	return Real_ExtTextOutW(hdc,X,Y,fuOptions,lprc,lpString,cbCount,lpDx);
}

