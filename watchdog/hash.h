/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#pragma once

//=================================================================================================
class IHash
{
public:
	enum HashType
	{
		Undef = 0,
		md5,
		sha256,
		sha384,
		sha512,
	};

	IHash();
	virtual ~IHash(){ }

	virtual bool init() = 0;
	virtual bool update(boost::shared_array<char>& data, unsigned long long size) = 0;
	virtual bool finalize() = 0;

	virtual std::string string(bool bRegen = false)const;

	static HashType typeFromStr(const std::string& name);
	static IHash* create(HashType type);

protected:
	boost::shared_ptr<void>				m_spec;
	boost::shared_array<unsigned char>	m_raw;
	mutable std::string					m_hash;

	virtual bool init_spec() = 0;
	virtual bool init_raw() = 0;
	virtual unsigned int hash_len()const = 0;
};

//=================================================================================================
class Md5Hash : public IHash
{
public:
	Md5Hash();
	~Md5Hash();

	virtual bool init() override;
	virtual bool update(boost::shared_array<char>& data, unsigned long long size) override;
	virtual bool finalize() override;

protected:
	virtual bool init_spec()override;
	virtual bool init_raw()override;
	virtual unsigned int hash_len()const override;
};

//=================================================================================================
class Sha256Hash : public IHash
{
public:
	Sha256Hash();
	~Sha256Hash();

protected:
	virtual bool init_spec()override;
	virtual bool init_raw()override;
	virtual unsigned int hash_len()const override;

public:
	virtual bool init() override;
	virtual bool update(boost::shared_array<char>& data, unsigned long long size) override;
	virtual bool finalize() override;
};

//=================================================================================================
class Sha384Hash : public IHash
{
public:
	Sha384Hash();
	~Sha384Hash();

protected:
	virtual bool init_spec()override;
	virtual bool init_raw()override;
	virtual unsigned int hash_len()const override;

public:
	virtual bool init() override;
	virtual bool update(boost::shared_array<char>& data, unsigned long long size) override;
	virtual bool finalize() override;
};

//=================================================================================================
class Sha512Hash : public IHash
{
public:
	Sha512Hash();
	~Sha512Hash();

protected:
	virtual bool init_spec()override;
	virtual bool init_raw()override;
	virtual unsigned int hash_len()const override;

public:
	virtual bool init() override;
	virtual bool update(boost::shared_array<char>& data, unsigned long long size) override;
	virtual bool finalize() override;
};

//=================================================================================================
