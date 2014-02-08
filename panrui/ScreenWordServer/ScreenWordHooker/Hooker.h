#include <detours.h>
#include <windows.h>

#pragma comment(lib, "detours.lib") 
#pragma comment(lib, "detoured.lib") 

#define MAX_SIZE 1024
#define PIPE_NAME "\\\\.\\Pipe\\screenword"


class Hooker
{
public:

	void Hook();
	void Unhook();
	
	static Hooker * getInstance();
	void communicationWithServerA(CHAR * info,UINT size ,UINT fuOptions);
	void communicationWithServerW(WCHAR * info,UINT size ,UINT fuOptions);

	~Hooker();

private:
	Hooker(const Hooker &);
	const Hooker & operator= (const Hooker &);

private:
	Hooker();

	HANDLE m_hPipe;
};

BOOL __stdcall Fake_TextOutA(HDC ,int ,int ,LPCSTR ,int );
BOOL __stdcall Fake_TextOutW(HDC ,int ,int ,LPCWSTR ,int );
BOOL __stdcall Fake_ExtTextOutA(HDC ,int ,int ,UINT ,CONST RECT * ,LPCSTR ,UINT ,CONST INT *);
BOOL __stdcall Fake_ExtTextOutW(HDC ,int ,int ,UINT ,CONST RECT * ,LPCWSTR ,UINT ,CONST INT *);