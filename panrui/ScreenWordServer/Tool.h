#define DEF_BUF_SIZE 260

void doListProcess();
DWORD getDesktopHandle();
BOOL WINAPI InjectLibW(DWORD dwProcessId, PCWSTR pszLibFile);
BOOL WINAPI EjectLibW(DWORD dwProcessId, PCWSTR pszLibFile);
