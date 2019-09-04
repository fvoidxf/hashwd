#pragma once

//=================================================================================================
class IFileData
{
public:
	virtual ~IFileData(){}

	virtual std::string fullname()const = 0;
	virtual void setName(const std::string& name) = 0;

	virtual time_t time()const = 0;
	virtual void setCurrentTime() = 0;

	virtual std::string make_hash(IHashData::Type type = IHashData::Gost2012) = 0;
	virtual std::streampos fileSize()const = 0;
	virtual bool HaveHash()const = 0;
	virtual std::string hash()const = 0;
};

//=================================================================================================
class FileData : public IFileData
{
public:
	FileData();
	explicit FileData(const std::string& fileName, time_t *_t = NULL, const std::string& hash = "");
	~FileData();

	virtual std::string fullname()const override;
	virtual void setName(const std::string& name) override;

	virtual std::streampos fileSize()const override;
	virtual std::string make_hash(IHashData::Type type = IHashData::Gost2012) override;

	virtual bool HaveHash()const override;
	virtual std::string hash()const override;

	virtual time_t time()const override;
	virtual void setCurrentTime() override;

protected:
	std::string m_filename;
	std::string m_hash;
	time_t      m_time;
};

//=================================================================================================
