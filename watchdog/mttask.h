#pragma once

#ifndef DB_SOURCE
	#define DB_SOURCE "watchdog.db"
#endif

class MidVal
{
public:
	char *fname;
	unsigned char *md5;
	time_t time;
};

//=============================================================================================
class MTTask
{
public:
	MTTask(const std::string& sRootDir, const std::string& dbname = DB_SOURCE);
	virtual ~MTTask();

	bool startInputThread();
	bool startGenerateThread();
	bool startOutputThread();

	void InputThreadJoin();
	void GenerateThreadJoin();
	void OutputThreadJoin();

protected:
	boost::lockfree::queue<char*, boost::lockfree::fixed_sized<false> >						m_inputFileList;
	boost::lockfree::queue<MidVal*, boost::lockfree::fixed_sized<false> >					m_md5List;

	std::string																																		m_root;
	std::string																																		m_dbname;

	boost::shared_ptr< std::thread >																							m_in,m_gen,m_out;

public:
	static void walkRoot(const std::string& root, boost::lockfree::queue<char*, boost::lockfree::fixed_sized<false> >* pQueue);
	static void md5Calc(boost::lockfree::queue<char*, boost::lockfree::fixed_sized<false> >* pInQueue, boost::lockfree::queue<MidVal*, boost::lockfree::fixed_sized<false> >* pMd5Queue);
	static void writeDb( boost::lockfree::queue<MidVal*, boost::lockfree::fixed_sized<false> >* pMd5Queue);

	static std::streampos filesize(const std::string& fname);
};

//=============================================================================================
