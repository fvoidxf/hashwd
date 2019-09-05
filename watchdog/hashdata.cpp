#include "stdafx.h"
#include "hashdata.h"

#define MD5_LENGTH 16
#define GOST89_LENGTH 32
#define GOST2012_LENGTH 64
#define GOST2012H_LENGTH GOST2012_LENGTH/2
#define GOST2012_BITS	512

//-------------------------------------------------------------------------------------------------
std::string IHashData::toString(unsigned char* hashvalue, size_t size)
{
	std::string result;
	std::stringstream ss;

	for(auto i = 0; i < size; i++)
		ss << std::hex << std::setfill('0') << std::setw(2) << (int)hashvalue[i];

	result = ss.str();

	return result;
}

//-------------------------------------------------------------------------------------------------
IHashData* IHashData::create(Type type)
{
	switch(type)
	{
	case MD5:return new Md5Data;
	case Gost89:return new Gost89Data;
	case Gost2012:return new Gost2012Data;
	}

	return nullptr;
}

//-------------------------------------------------------------------------------------------------
IHashData::IHashData()
	:m_hashData(0)
	,m_hashSize(0)
{

}


//-------------------------------------------------------------------------------------------------
Md5Data::Md5Data()
	:IHashData()
{

}

//-------------------------------------------------------------------------------------------------
Md5Data::~Md5Data()
{

}

//-------------------------------------------------------------------------------------------------
bool Md5Data::init()
{
	MD5_Init(&m_ctx);
	m_hashSize = MD5_LENGTH;
	try
	{
		m_hashData = new unsigned char[m_hashSize];
	}
	catch(...)
	{
		m_hashSize = 0;
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Md5Data::hash(unsigned char* data, size_t size)
{
	if(!data)
		return false;
	if(!size)
		return false;
	if(!m_hashData)
		return false;

	MD5_Update(&m_ctx, data, size);

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Md5Data::finish()
{
	if(!m_hashData)
		return false;
	if(!m_hashSize)
		return false;

	MD5_Final(m_hashData, &m_ctx);

	return true;
}

//-------------------------------------------------------------------------------------------------
IHashData::Type Md5Data::type()const
{
	return MD5;
}

//-------------------------------------------------------------------------------------------------
std::string Md5Data::str()const
{
	if(m_humanReadable.empty())
		m_humanReadable = toString(m_hashData, m_hashSize);
	return m_humanReadable;
}

//-------------------------------------------------------------------------------------------------
Gost89Data::Gost89Data()
	:IHashData()
	,m_subst(nullptr)
{

}

//-------------------------------------------------------------------------------------------------
Gost89Data::~Gost89Data()
{

}

//-------------------------------------------------------------------------------------------------
bool Gost89Data::init()
{
	if(!m_subst)
		m_subst = &GostR3411_94_CryptoProParamSet;

	start_hash(&m_ctx);
	init_gost_hash_ctx(&m_ctx, m_subst);

	m_hashSize = GOST89_LENGTH;
	try
	{
		m_hashData = new unsigned char[m_hashSize];
	}
	catch(...)
	{
		m_hashSize = 0;
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Gost89Data::hash(unsigned char* data, size_t size)
{
	if(!m_hashData)
		return false;
	if(!m_hashSize)
		return false;
	if(!data || !size)
		return false;

	hash_block(&m_ctx, data, size);

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Gost89Data::finish()
{
	if(!m_hashData)
		return false;
	if(!m_hashSize)
		return false;

	finish_hash(&m_ctx, m_hashData);
	done_gost_hash_ctx(&m_ctx);

	return true;
}

//-------------------------------------------------------------------------------------------------
IHashData::Type Gost89Data::type()const
{
	return Gost89;
}

//-------------------------------------------------------------------------------------------------
std::string Gost89Data::str()const
{
	if(m_humanReadable.empty())
		m_humanReadable = toString(m_hashData, m_hashSize);
	return m_humanReadable;
}

//------------------------------------------------------------------------------------------------- 
Gost2012Data::Gost2012Data()
	:IHashData()
{

}

//-------------------------------------------------------------------------------------------------
Gost2012Data::~Gost2012Data()
{

}

//-------------------------------------------------------------------------------------------------
bool Gost2012Data::init()
{
	init_gost2012_hash_ctx(&m_ctx, GOST2012_BITS);
	m_hashSize = GOST2012_BITS/8;
	try
	{
		m_hashData = new unsigned char[m_hashSize];
	}
	catch(...)
	{
		m_hashSize = 0;
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Gost2012Data::hash(unsigned char* data, size_t size)
{
	if(!data || !size)
		return false;
	if(!m_hashSize || !m_hashData)
		return false;
	gost2012_hash_block(&m_ctx, data, size);
	return true;
}
//-------------------------------------------------------------------------------------------------
bool Gost2012Data::finish()
{
	if(!m_hashSize || !m_hashData)
		return false;
	gost2012_finish_hash(&m_ctx, m_hashData);
	return true;
}

//-------------------------------------------------------------------------------------------------
IHashData::Type Gost2012Data::type()const
{
	return Gost2012;
}

//-------------------------------------------------------------------------------------------------
std::string Gost2012Data::str()const
{
	if(m_humanReadable.empty())
		m_humanReadable = toString(m_hashData, m_hashSize);
	return m_humanReadable;
}

//-------------------------------------------------------------------------------------------------
Sha256Data::Sha256Data()
	:IHashData()
{

}

//-------------------------------------------------------------------------------------------------
Sha256Data::~Sha256Data()
{

}

//-------------------------------------------------------------------------------------------------
bool Sha256Data::init()
{
	SHA256_Init(&m_ctx);
	m_hashSize = SHA256_DIGEST_LENGTH;
	try
	{
		m_hashData = new unsigned char[m_hashSize];
	}
	catch(...)
	{
		m_hashSize = 0;
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha256Data::hash(unsigned char* data, size_t size)
{
	if(!m_hashData)
		return false;
	if(!m_hashSize)
		return false;
	if(!data || !size)
		return false;

	SHA256_Update(&m_ctx, data, size);

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha256Data::finish()
{
	if(!m_hashSize || !m_hashData)
		return false;
	SHA256_Final(m_hashData, &m_ctx);
	return true;
}

//-------------------------------------------------------------------------------------------------
IHashData::Type Sha256Data::type()const
{
	return Sha256;
}

//-------------------------------------------------------------------------------------------------
std::string Sha256Data::str()const
{
	if(m_humanReadable.empty())
		m_humanReadable = toString(m_hashData, m_hashSize);
	return m_humanReadable;
}

//-------------------------------------------------------------------------------------------------
Sha384Data::Sha384Data()
{

}

//-------------------------------------------------------------------------------------------------
Sha384Data::~Sha384Data()
{

}

//-------------------------------------------------------------------------------------------------
bool Sha384Data::init()
{
	SHA384_Init(&m_ctx);
	m_hashSize = SHA384_DIGEST_LENGTH;
	try
	{
		m_hashData = new unsigned char[m_hashSize];
	}
	catch(...)
	{
		m_hashSize = 0;
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha384Data::hash(unsigned char* data, size_t size)
{
	if(!m_hashData)
		return false;
	if(!m_hashSize)
		return false;
	if(!data || !size)
		return false;

	SHA384_Update(&m_ctx, data, size);

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha384Data::finish()
{
	if(!m_hashSize || !m_hashData)
		return false;
	SHA384_Final(m_hashData, &m_ctx);
	return true;
}

//-------------------------------------------------------------------------------------------------
IHashData::Type Sha384Data::type()const
{
	return Sha384;
}

//-------------------------------------------------------------------------------------------------
std::string Sha384Data::str()const
{
	if(m_humanReadable.empty())
		m_humanReadable = toString(m_hashData, m_hashSize);
	return m_humanReadable;
}

//-------------------------------------------------------------------------------------------------
Sha512Data::Sha512Data()
{

}

//-------------------------------------------------------------------------------------------------
Sha512Data::~Sha512Data()
{

}

//-------------------------------------------------------------------------------------------------
bool Sha512Data::init()
{
	SHA512_Init(&m_ctx);
	m_hashSize = SHA512_DIGEST_LENGTH;
	try
	{
		m_hashData = new unsigned char[m_hashSize];
	}
	catch(...)
	{
		m_hashSize = 0;
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha512Data::hash(unsigned char* data, size_t size)
{
	if(!m_hashData)
		return false;
	if(!m_hashSize)
		return false;
	if(!data || !size)
		return false;

	SHA512_Update(&m_ctx, data, size);

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha512Data::finish()
{
	if(!m_hashSize || !m_hashData)
		return false;
	SHA512_Final(m_hashData, &m_ctx);
	return true;
}

//-------------------------------------------------------------------------------------------------
IHashData::Type Sha512Data::type()const
{
	return Sha512;
}

//-------------------------------------------------------------------------------------------------
