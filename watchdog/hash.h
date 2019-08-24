/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#pragma once

//=================================================================================================
class IHash
{
public:
	IHash();
	virtual ~IHash(){ }

	virtual bool init();
	virtual bool update(boost::shared_array<char>& data, unsigned long long size) = 0;
	virtual bool finalize() = 0;

	virtual std::string string(bool bRegen = false)const;

protected:
	boost::shared_ptr<void>				m_spec;
	boost::shared_array<unsigned char>	m_raw;
	mutable std::string					m_hash;

	virtual bool init_spec() = 0;
	virtual bool init_raw() = 0;
};

//=================================================================================================
class Md5Hash : public IHash
{
public:
	Md5Hash();
	~Md5Hash();

	virtual bool update(boost::shared_array<char>& data, unsigned long long size) override;
	virtual bool finalize() override;

protected:
	virtual bool init_spec()override;
	virtual bool init_raw()override;
};

//=================================================================================================

//=================================================================================================
