/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#include "stdafx.h"
#include "filedata.h"
#include "hash.h"

#pragma warning( disable: 4244 )

//-------------------------------------------------------------------------------------------------
FileData::FileData()
{

}

//-------------------------------------------------------------------------------------------------
FileData::FileData(const std::string& fileName, time_t *_t /*= NULL*/, const std::string& md5 /*= ""*/)
	:m_filename(fileName)
{
	if (!md5.empty())
		m_md5 = md5;
	if (_t)
		m_time = *_t;
}

//------------------------------------------------------------------------------------------------- 
FileData::~FileData()
{

}

//-------------------------------------------------------------------------------------------------
std::string FileData::fullname()const
{
	return m_filename;
}

//------------------------------------------------------------------------------------------------- 
void FileData::setName(const std::string& name)
{
	m_filename = name;
}

//-------------------------------------------------------------------------------------------------
std::string FileData::make_md5()
{
	std::string md5str;

	std::ifstream _in(fullname(), std::ios::binary);

	std::streamoff fileSize = this->fileSize();

	if(!fileSize)
		return md5str;

	boost::shared_array<char> pArr(new char[fileSize]);

	while(!_in.eof()){
		_in.read(  pArr.get(), fileSize);
	}

	_in.close();

	boost::shared_ptr<IHash> pHash(new Md5Hash);
	pHash->init();
	pHash->update(pArr, fileSize);
	pHash->finalize();

	m_md5 = pHash->string();

	return md5str;
}

//------------------------------------------------------------------------------------------------- 
std::streampos FileData::fileSize()const
{
	std::streampos fsize = 0;

	std::ifstream file(fullname(), std::ios::binary);

	fsize = file.tellg();
	file.seekg( 0, std::ios::end );
	fsize = file.tellg() - fsize;

	file.close();

	return fsize;
}

//-------------------------------------------------------------------------------------------------
bool FileData::HaveMD5()const
{
	return !m_md5.empty();
}

//-------------------------------------------------------------------------------------------------
std::string FileData::md5()const
{
	return m_md5;
}

//-------------------------------------------------------------------------------------------------
time_t FileData::time()const
{
	return m_time;
}

//-------------------------------------------------------------------------------------------------
void FileData::setCurrentTime()
{
	::time(&m_time);
}

//-------------------------------------------------------------------------------------------------
