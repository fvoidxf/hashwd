#ifndef __HASHDATA_H__
#define __HASHDATA_H__

//=================================================================================================
class IHashData
{
public:
	enum Type
	{
		UndefHash = 0,
		MD5,
		Gost89,
		Gost2012,
		Gost2012h,
		Sha256,
		Sha384,
		Sha512,
	};

	virtual ~IHashData(){ if(m_hashData)delete[] m_hashData; }

	static std::string toString(unsigned char* hashvalue, size_t size);
	static IHashData* create(Type type);

	virtual bool init() = 0;
	virtual bool hash(unsigned char* data, size_t size) = 0;
	virtual bool finish() = 0;
	virtual Type type()const = 0;
	virtual std::string str()const = 0;

	size_t hashSize()const { return m_hashSize; }
	void* raw(){ return static_cast<void*>(m_hashData); }

protected:
	mutable std::string		m_humanReadable;
	unsigned char					*m_hashData;
	size_t								m_hashSize;

	IHashData();
};

//=================================================================================================
class Md5Data : public IHashData
{
public:
	Md5Data();
	~Md5Data();

	virtual bool init()override;
	virtual bool hash(unsigned char* data, size_t size) override;
	virtual bool finish() override;
	virtual Type type()const override;
	virtual std::string str()const override;

protected:
	MD5_CTX								m_ctx;
};

//=================================================================================================
class Gost89Data : public IHashData
{
public:
	Gost89Data();
	~Gost89Data();

	virtual bool init()override;
	virtual bool hash(unsigned char* data, size_t size) override;
	virtual bool finish() override;
	virtual Type type()const override;
	virtual std::string str()const override;

protected:
	gost_hash_ctx						m_ctx;
	gost_subst_block				*m_subst;
};

//================================================================================================= 
class Gost2012Data : public IHashData
{
public:
	Gost2012Data();
	~Gost2012Data();

	virtual bool init()override;
	virtual bool hash(unsigned char* data, size_t size) override;
	virtual bool finish() override;
	virtual Type type()const override;
	virtual std::string str()const override;

protected:
	gost2012_hash_ctx					m_ctx;
};

//=================================================================================================
class Sha256Data : public IHashData
{
public:
	Sha256Data();
	~Sha256Data();

	virtual bool init()override;
	virtual bool hash(unsigned char* data, size_t size) override;
	virtual bool finish() override;
	virtual Type type()const override;
	virtual std::string str()const override;

protected:
	SHA256_CTX m_ctx;
};

//================================================================================================= 
class Sha384Data : public IHashData
{
public:
	Sha384Data();
	~Sha384Data();

	virtual bool init()override;
	virtual bool hash(unsigned char* data, size_t size) override;
	virtual bool finish() override;
	virtual Type type()const override;
	virtual std::string str()const override;

protected:
	SHA512_CTX m_ctx;
};

//================================================================================================= 
class Sha512Data : public Sha384Data
{
public:
	Sha512Data();
	~Sha512Data();

	virtual bool init()override;
	virtual bool hash(unsigned char* data, size_t size) override;
	virtual bool finish() override;
	virtual Type type()const override;
};

//=================================================================================================

#endif
