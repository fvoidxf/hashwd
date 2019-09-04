#pragma once

#ifndef DB_SOURCE
	#define DB_SOURCE "watchdog.db"
#endif

class DbSource;

//=================================================================================================
class IFDContainer
{
public:
	typedef struct DIFFS {
		std::string filename;
		std::string wasMD5;
		std::string nowMD5;
	}*LPDIFFS;

	virtual ~IFDContainer(){}

	virtual void setRoot(const std::string& rootDir) = 0;
	virtual bool walk() = 0;

	virtual void add(const std::string& fileName, time_t *_t = NULL, const std::string& md5 = "") = 0;

	virtual void show() = 0;
	virtual void check_files() = 0;
	virtual void diff(std::list<DIFFS>& diffList) = 0;

	virtual bool connect() = 0;
	virtual void close() = 0;
	virtual bool isSessionExists() = 0;

	virtual bool create_session() = 0;
	virtual void saveSession() = 0;
	virtual void loadSession() = 0;
};

//=================================================================================================
class FDContainer : public IFDContainer
{
public:
	FDContainer(const std::string &session, const std::string& dbname = DB_SOURCE);
	~FDContainer();

	virtual void setRoot(const std::string& rootDir) override;
	virtual bool walk() override;
	virtual void add(const std::string& fileName, time_t *_t = NULL, const std::string& md5 = "")override;
	virtual void show() override;
	virtual void check_files() override;
	virtual void diff(std::list<DIFFS>& diffList) override;

	virtual bool connect()override;
	virtual void close() override;

	virtual bool isSessionExists()override;
	virtual bool create_session() override;
	virtual void saveSession() override;
	virtual void loadSession() override;

protected:
	std::string m_root;
	DbSource    m_db;
	std::list<boost::shared_ptr<IFileData> > m_list;

	bool m_r_walk(const boost::filesystem::path &loc);
};

//=================================================================================================
