/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#include "stdafx.h"
#include "getfiledata.h"
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
bool GetFileData(const std::string& filename, boost::shared_array<char>& data, unsigned long long filesize)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;

	if (filesize == 0)
		return false;

	if (data.get())
		return false;

	if (filename.empty())
		return false;

	hFile = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	try
	{
		data.reset(new char[filesize]);
	}
	catch (std::bad_alloc& e)
	{
		std::cerr << "Bad allocation: " << e.what() << std::endl;
		CloseHandle(hFile);
		return false;
	}
	DWORD rd = 0;
	BOOL bRes = ReadFile(hFile, data.get(), filesize, &rd, NULL);
	if (!bRes || (rd < filesize))
	{
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);

	return true;
}

//-------------------------------------------------------------------------------------------------
