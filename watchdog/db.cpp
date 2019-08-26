/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#include "stdafx.h"
#include "db.h"
#include "filedata.h"
#include "filecontainer.h"

#pragma warning( disable : 4996 )

#define SERVICE_TABLE					"sqlite_master"

#define INSERT_STMT_PREPARE				"INSERT INTO %s (filename,time,md5) VALUES(?,?,?)"
#define CREATE_TABLE					"CREATE TABLE %s (id INTEGER PRIMARY KEY ASC AUTOINCREMENT UNIQUE NOT NULL DEFAULT (1), filename VARCHAR(1024), time DATETIME, md5 VARCHAR(64));"
#define GET_SESSIONS					"SELECT * FROM sqlite_master WHERE type=\'table\'"
#define SELECT_MAIN						"SELECT filename,time,md5 FROM %s"

//-------------------------------------------------------------------------------------------------
DbSource::DbSource(const std::string &session, const std::string& dbname /*= DB_SOURCE*/)
	:m_db(0)
	,m_session(session)
	,m_name(dbname)
{

}

//-------------------------------------------------------------------------------------------------
DbSource::~DbSource()
{

}

//------------------------------------------------------------------------------------------------- 
std::string DbSource::db_name()const
{
	return m_name;
}

//-------------------------------------------------------------------------------------------------
bool DbSource::open()
{
	return SQLITE_OK == sqlite3_open(m_name.c_str(), &m_db);
}

//-------------------------------------------------------------------------------------------------
void DbSource::close()
{
	sqlite3_close(m_db);
}

//-------------------------------------------------------------------------------------------------
bool DbSource::addData(const std::string& filename, time_t _time, const std::string& md5)
{
	char localBuff[1024];
	memset(localBuff, 0, 1024);
	sprintf(localBuff, INSERT_STMT_PREPARE, m_session.c_str());

	int rc = 0;
	sqlite3_stmt *stmt = 0;
	rc = sqlite3_prepare_v2(m_db, localBuff, -1, &stmt, 0);
	rc = sqlite3_bind_text(stmt, 1, filename.c_str(), filename.size(), 0);
	rc = sqlite3_bind_int64(stmt, 2, _time);
	rc = sqlite3_bind_text(stmt, 3, md5.c_str(), md5.size(), 0);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return true;
}

//-------------------------------------------------------------------------------------------------
bool DbSource::isSessionExists()const
{
	bool bRes = false;
	int rc = 0;
	char *err = 0;
	sqlite3_stmt *stmt = 0;
	rc = sqlite3_prepare_v2(m_db, GET_SESSIONS, -1, &stmt, 0);
	rc = sqlite3_bind_text(stmt, 1, SERVICE_TABLE, strlen(SERVICE_TABLE), 0);

	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		std::string val(reinterpret_cast<const char*>(sqlite3_column_text(stmt,1)));
		if(val == m_session)
			bRes = true;
	}

	sqlite3_finalize(stmt);

	return bRes;
}

//-------------------------------------------------------------------------------------------------
bool DbSource::create_session()
{
	char *err = 0;
	char LocBuf[512];
	memset(LocBuf, 0, 512);

	sprintf( LocBuf, CREATE_TABLE, m_session.c_str() );

	int rc = sqlite3_exec(m_db, LocBuf, 0, 0, &err);
	return true;
}

//-------------------------------------------------------------------------------------------------
void DbSource::load_session(IFDContainer *_cnt)
{
	char *err = 0;
	char LocBuf[512];
	memset(LocBuf, 0, 512);

	sprintf(LocBuf, SELECT_MAIN, m_session.c_str());
	sqlite3_stmt *stmt = 0;
	int rc = sqlite3_prepare_v2(m_db, LocBuf, -1, &stmt, 0);
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		char *fnm = (char*)sqlite3_column_text(stmt, 0);
		time_t _t = sqlite3_column_int64(stmt, 1);
		char *md5 = (char*)sqlite3_column_text(stmt, 2);

		if(fnm && md5)
			_cnt->add(fnm, 0, md5);
	}
}

//------------------------------------------------------------------------------------------------- 