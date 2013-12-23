#include "CLFileTraverser.h"
#include <Windows.h>

CLFileTraverser::CLFileTraverser():m_fileList(NULL)
{

}

CLFileTraverser::~CLFileTraverser()
{

}

list<string > * CLFileTraverser::TraversingFile(string & v_path)
{
	WIN32_FIND_DATA fdFileData;
	HANDLE hFind;

	m_fileList = new list<string >;

	hFind = FindFirstFile((v_path+"\\*.h").c_str(),&fdFileData);

	if(hFind == INVALID_HANDLE_VALUE )
	{
		return m_fileList;
	}

	do{
		m_fileList->push_back(v_path +"\\" + fdFileData.cFileName);

	}while(FindNextFile(hFind,&fdFileData )!= 0);
	
	return m_fileList;
}
