/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#pragma once

#ifndef DB_SOURCE
	#define DB_SOURCE "watchdog.db"
#endif

//=============================================================================================
class MTTask
{
public:
	class HashData
	{
	public:
		time_t time;
		std::string filename;
		std::string md5;
	};

	typedef boost::lockfree::queue< HashData*, boost::lockfree::fixed_sized<false> > QueueT;

	MTTask(const std::string& sRootDir, const std::string& dbname = DB_SOURCE);
	virtual ~MTTask();

	bool startInputThread();
	bool startGenerateThread();
	bool startOutputThread();

	void InputThreadJoin();
	void GenerateThreadJoin();
	void OutputThreadJoin();

protected:
	QueueT										m_qIn, m_qMd5;

	std::string									m_root;
	std::string									m_dbname;

	boost::shared_ptr< std::thread >			m_in,m_gen,m_out;
	static bool																				m_flag[3];

public:
	static void walkRoot(const std::string& root, QueueT* Queue);
	static void md5Calc(QueueT* Queue, QueueT* pMd5Queue);
	static void writeDb(QueueT* pMd5Queue);
};

//=============================================================================================
