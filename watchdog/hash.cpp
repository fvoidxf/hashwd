/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/
#include "stdafx.h"
#include "hash.h"

#ifndef MD5_RAW_SZ
	#define MD5_RAW_SZ 16
#endif

//-------------------------------------------------------------------------------------------------
IHash* IHash::create(IHash::HashType type)
{
	switch (type)
	{
	case IHash::md5:
		return new Md5Hash;
	case IHash::sha256:
		return new Sha256Hash;
	case IHash::sha384:
		return new Sha384Hash;
	case IHash::sha512:
		return new Sha512Hash;
	}
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
std::string IHash::string(bool bRegen /*= false*/)const
{
	if (bRegen && m_raw.get())
	{
		std::stringstream ss;
		for (auto i = 0; i < MD5_RAW_SZ; i++)
			ss << std::hex << std::setfill('0') << std::setw(2) << (int)m_raw[i];
		m_hash = ss.str();
	}

	if (m_hash.empty())
	{
		if (m_raw.get())
		{
			std::stringstream ss;
			for (auto i = 0; i < MD5_RAW_SZ; i++)
				ss << std::hex << std::setfill('0') << std::setw(2) << (int)m_raw[i];
			m_hash = ss.str();
		}
	}
	return m_hash;
}

//-------------------------------------------------------------------------------------------------
IHash::IHash()
	:m_spec(0)
	,m_raw(0)
{

}

//-------------------------------------------------------------------------------------------------
Md5Hash::Md5Hash()
	:IHash()
{

}

//-------------------------------------------------------------------------------------------------
Md5Hash::~Md5Hash()
{

}

//-------------------------------------------------------------------------------------------------
bool IHash::init()
{
	if (!init_spec())
		return false;
	return MD5_Init(static_cast<MD5_CTX*>(m_spec.get())) != 0;
}

//-------------------------------------------------------------------------------------------------
bool Md5Hash::update(boost::shared_array<char>& data, unsigned long long size)
{
	if( (data.get() == nullptr) || (!size) )
		return false;
	if( m_spec.get() == nullptr )
		return false;
	return MD5_Update(static_cast<MD5_CTX*>(m_spec.get()), data.get(), size) != 0;
}

//-------------------------------------------------------------------------------------------------
bool Md5Hash::finalize()
{
	if (m_spec.get() == nullptr)
		return false;
	if (!init_raw())
		return false;
	return MD5_Final(m_raw.get(), static_cast<MD5_CTX*>(m_spec.get())) != 0;
}

//-------------------------------------------------------------------------------------------------
bool Md5Hash::init_spec()
{
	try
	{
		m_spec.reset(new MD5_CTX);
	}
	catch (std::exception& e)
	{
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Md5Hash::init_raw()
{
	try
	{
		m_raw.reset( new unsigned char[MD5_RAW_SZ] );
	}
	catch (std::exception& e)
	{
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
IHash::HashType IHash::typeFromStr(const std::string& name)
{
	HashType hType = Undef;

	if (name == "md5")
		hType = md5;
	else if (name == "sha256")
		hType = sha256;
	else if (name == "sha384")
		hType = sha384;
	else if (name == "sha512")
		hType = sha512;

	return hType;
}

//-------------------------------------------------------------------------------------------------
Sha256Hash::Sha256Hash()
	:IHash()
{

}

//-------------------------------------------------------------------------------------------------
Sha256Hash::~Sha256Hash()
{

}

//-------------------------------------------------------------------------------------------------
bool Sha256Hash::init_spec()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha256Hash::init_raw()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha256Hash::update(boost::shared_array<char>& data, unsigned long long size)
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha256Hash::finalize()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
Sha384Hash::Sha384Hash()
	:IHash()
{

}

//-------------------------------------------------------------------------------------------------
Sha384Hash::~Sha384Hash()
{

}

//-------------------------------------------------------------------------------------------------
bool Sha384Hash::init_spec()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha384Hash::init_raw()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha384Hash::update(boost::shared_array<char>& data, unsigned long long size)
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha384Hash::finalize()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
Sha512Hash::Sha512Hash()
	:IHash()
{

}

//-------------------------------------------------------------------------------------------------
Sha512Hash::~Sha512Hash()
{

}

//-------------------------------------------------------------------------------------------------
bool Sha512Hash::init_spec()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha512Hash::init_raw()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha512Hash::update(boost::shared_array<char>& data, unsigned long long size)
{
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Sha512Hash::finalize()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
