// ScreenWordHooker.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Hooker.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	Hooker * phk;

	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			phk = Hooker::getInstance();
			phk->Hook();

			break;
		}
	case DLL_PROCESS_DETACH:
		{
			phk = Hooker::getInstance();
			phk->Unhook();

			delete phk;

			break;
		}
	}
    return TRUE;
}

