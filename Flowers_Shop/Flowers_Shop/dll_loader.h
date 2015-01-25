#ifndef _DLL_LOADER_H_
#define _DLL_LOADER_H_

class dllLoader
{
private:
	int m_nFilesCount;
	TCHAR *m_pFilesNames;
	HMODULE *m_pHMod;
public:
	dllLoader();
	~dllLoader();
};

#endif _DLL_LOADER_H_