#include "stdafx.h"
#include "dll_loader.h"


dllLoader::dllLoader()
{
	const int MAX_DIR_PATH = 255;
	TCHAR CurDirectory[MAX_DIR_PATH];
	GetCurrentDirectory(MAX_DIR_PATH, CurDirectory);
	m_nFilesCount = 0;
	int i = 0;
	while(CurDirectory[i] != '\0')
	{
		if(CurDirectory[i] == '\\')
			CurDirectory[i] = '/';
		++i;
	}
	lstrcatW(CurDirectory, L"/*.dll");
	MessageBox(NULL, CurDirectory, L"Mess", MB_OK);
	WIN32_FIND_DATA wfd;
	WIN32_FIND_DATA wfd2;
	HANDLE hFind = FindFirstFile(CurDirectory, &wfd);
	//HANDLE const hFind2 = FindFirstFile(CurDirectory, &wfd2);

	if(INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
				++m_nFilesCount;
		}while(NULL != FindNextFile(hFind, &wfd));

	}
	TCHAR df[255];
	//df[4] = '\0';
	wsprintf(df, L"%d", m_nFilesCount);
	MessageBox(NULL, df, L"Mess", MB_OK);

	i = 0;
	hFind = FindFirstFile(CurDirectory, &wfd);
	m_pFilesNames = new WCHAR*[m_nFilesCount];
	if(INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			m_pFilesNames[i] = new WCHAR[lstrlen(wfd.cFileName)+1];
			lstrcpy(m_pFilesNames[i++], wfd.cFileName);			
		}while(NULL != FindNextFile(hFind, &wfd));

	}
	wsprintf(df, L"%d", i);
	MessageBox(NULL, df, L"Mess", MB_OK);
	for(i = 0; i < m_nFilesCount; ++i)
		MessageBox(NULL, (m_pFilesNames[i]), L"Mess", MB_OK);
	m_pHMod = new HMODULE[m_nFilesCount];
	for(i = 0; i < m_nFilesCount; ++i)
	{
		m_pHMod[i] = LoadLibrary(m_pFilesNames[i]);
	}

}

dllLoader::~dllLoader()
{
	MessageBox(NULL, m_pFilesNames[0], L"Mess", MB_OK);
	for(int i = 0; i < m_nFilesCount; ++i)
	{
		FreeLibrary(m_pHMod[i]);
		delete []m_pFilesNames[i];
	}
	delete []m_pHMod;
	delete []m_pFilesNames;	
}

