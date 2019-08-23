/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#include "stdafx.h"
#include "mttask.h"
#include "filesize.h"
#include "getfiledata.h"

//bool MTTask::m_flag[2];

//-------------------------------------------------------------------------------------------------
MTTask::MTTask(const std::string& sRootDir, const std::string& dbname )
	:m_root(sRootDir)
	,m_dbname(dbname)
	,m_inputFileList(0)
	,m_md5List(0)
	,m_in(NULL)
	,m_gen(NULL)
	,m_out(NULL)
{
	//m_flag[0] = true;
	//m_flag[1] = true;
}

//-------------------------------------------------------------------------------------------------
MTTask::~MTTask()
{

}

//-------------------------------------------------------------------------------------------------
void MTTask::walkRoot(const std::string& root, boost::lockfree::queue<char*, boost::lockfree::fixed_sized<false> >* pQueue)
{
	using namespace boost::filesystem;

	recursive_directory_iterator dir(root), end;

	while(dir != end)
	{
		const std::string sPath = dir->path().string();
		if(!sPath.empty())
		{
			char *buf = new char[sPath.size() + 1];
			buf[sPath.size()] = '\0';
			memcpy(buf,sPath.c_str(),sPath.size());
			pQueue->push(buf);
		}
		dir++;
	}
}

//-------------------------------------------------------------------------------------------------
void MTTask::md5Calc(boost::lockfree::queue<char*, boost::lockfree::fixed_sized<false> >* pInQueue, boost::lockfree::queue<MidVal*, boost::lockfree::fixed_sized<false> >* pMd5Queue)
{
	//while (m_flag[0])
	//{
		while (!pInQueue->empty())
		{
			char *pName = 0;
			pInQueue->pop(pName);
			try
			{
				if (pName)
				{
					unsigned long long fdatalen = FileSize(pName);

					if (!fdatalen)
						continue;

					MidVal* pMid = new MidVal;
					pMid->fname = pName;
					::time(&pMid->time);
					pMid->md5 = new unsigned char[16];

					char *pFileData = NULL;
					unsigned char *md5raw = new unsigned char[16];

					GetFileData(pName, pFileData, fdatalen);

					MD5_CTX ctx;
					MD5_Init(&ctx);
					MD5_Update(&ctx, pFileData, fdatalen);
					MD5_Final(md5raw, &ctx);

					std::stringstream ss;

					for (int i = 0; i < 16; i++)
					{
						ss << std::hex << std::setfill('0') << std::setw(2) << (int)md5raw[i];
					}

					strcpy((char*)pMid->md5, ss.str().c_str());

					pMd5Queue->push(pMid);
					delete[] pFileData;
				}
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	//}
}

//-------------------------------------------------------------------------------------------------
void MTTask::writeDb( boost::lockfree::queue<MidVal*, boost::lockfree::fixed_sized<false> >* pMd5Queue)
{
	//while (m_flag[1])
	//{
		while (!pMd5Queue->empty())
		{
			MidVal *pVal = 0;
			pMd5Queue->pop(pVal);
			std::cout << "Filename: " << pVal->fname << " MD5: " << pVal->md5 << "\r\n";
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(150));
	//}
}

//-------------------------------------------------------------------------------------------------
bool MTTask::startInputThread()
{
	m_in.reset( new std::thread(&MTTask::walkRoot, m_root, &m_inputFileList) );
	return m_in.get() != NULL;
}

//-------------------------------------------------------------------------------------------------
bool MTTask::startGenerateThread()
{
	m_gen.reset( new std::thread(&MTTask::md5Calc, &m_inputFileList, &m_md5List) );
	return m_gen.get() != NULL;
}

//-------------------------------------------------------------------------------------------------
bool MTTask::startOutputThread()
{
	m_out.reset( new std::thread( &MTTask::writeDb, &m_md5List ) );
	return m_out.get() != NULL;
}

//-------------------------------------------------------------------------------------------------
void MTTask::InputThreadJoin()
{
	m_in->join();
	//m_flag[0] = false;
}

//-------------------------------------------------------------------------------------------------
void MTTask::GenerateThreadJoin()
{
	m_gen->join();
	//m_flag[1] = false;
}

//-------------------------------------------------------------------------------------------------
void MTTask::OutputThreadJoin()
{
	m_out->join();
}

//-------------------------------------------------------------------------------------------------
