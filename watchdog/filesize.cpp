/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#include "stdafx.h"
#include "filesize.h"
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
unsigned long long FileSize(const std::string& filename)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	unsigned long long fsize = 0;

	if (filename.empty())
		return fsize;

	hFile = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER li;
		BOOL bRes = GetFileSizeEx(hFile, &li);
		if (!bRes)
		{
			CloseHandle(hFile);
			return fsize;
		}
		else
		{
			fsize = li.QuadPart;
			CloseHandle(hFile);
			return fsize;
		}
	}

	return fsize;
}

//-------------------------------------------------------------------------------------------------
