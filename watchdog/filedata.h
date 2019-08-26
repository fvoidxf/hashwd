/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/
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

	virtual std::string make_md5() = 0;
	virtual std::streampos fileSize()const = 0;
	virtual bool HaveMD5()const = 0;
	virtual std::string md5()const = 0;
};

//=================================================================================================
class FileData : public IFileData
{
public:
	FileData();
	explicit FileData(const std::string& fileName, time_t *_t = NULL, const std::string& md5 = "");
	~FileData();

	virtual std::string fullname()const override;
	virtual void setName(const std::string& name) override;

	virtual std::streampos fileSize()const override;
	virtual std::string make_md5() override;

	virtual bool HaveMD5()const override;
	virtual std::string md5()const override;

	virtual time_t time()const override;
	virtual void setCurrentTime() override;

protected:
	std::string m_filename;
	std::string m_md5;
	time_t      m_time;
};

//=================================================================================================
