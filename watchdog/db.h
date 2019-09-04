#pragma once

#ifndef DB_SOURCE
	#define DB_SOURCE "watchdog.db"
#endif

class FDContainer;
class IFDContainer;

//=================================================================================================
class DbSource
{
	friend class FDContainer;
private:
	sqlite3							*m_db;
	const std::string				m_name;
	std::string						m_session;

public:
	DbSource(const std::string &session, const std::string& dbname = DB_SOURCE);
	virtual ~DbSource();

	std::string db_name()const;
	std::string db_session()const;

	bool isSessionExists()const;

	bool open();
	void close();
	bool create_session();
	void load_session(IFDContainer *_cnt);

	bool addData(const std::string& filename, time_t _time, const std::string& md5);
};

//=================================================================================================
