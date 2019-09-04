#include "stdafx.h"
#include "filedata.h"

#pragma warning( disable: 4244 )

//-------------------------------------------------------------------------------------------------
FileData::FileData()
{

}

//-------------------------------------------------------------------------------------------------
FileData::FileData(const std::string& fileName, time_t *_t /*= NULL*/, const std::string& hash /*= ""*/)
	:m_filename(fileName)
{
	if (!hash.empty())
		m_hash = hash;
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
std::string FileData::make_hash(IHashData::Type type)
{
	std::string md5str;

	std::ifstream _in(fullname(), std::ios::binary);

	std::streamoff fileSize = this->fileSize();

	if(!fileSize)
		return md5str;

	boost::shared_array<unsigned char> pArr(new unsigned char[fileSize]);

	while(!_in.eof()){
		_in.read( reinterpret_cast<char*>( pArr.get() ), fileSize);
	}

	_in.close();

	IHashData *pHashing = IHashData::create(type);
	if(pHashing)
	{
		bool bRes = pHashing->init();
		if(bRes)
		{
			bRes = pHashing->hash(pArr.get(), fileSize);
			if(bRes)
			{
				pHashing->finish();
				m_hash = pHashing->str();
			}
		}
		delete pHashing;
	}

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
bool FileData::HaveHash()const
{
	return !m_hash.empty();
}

//-------------------------------------------------------------------------------------------------
std::string FileData::hash()const
{
	return m_hash;
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
