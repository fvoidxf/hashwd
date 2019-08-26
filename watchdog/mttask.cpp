/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#include "stdafx.h"
#include "hash.h"
#include "filesize.h"
#include "getfiledata.h"
#include "mttask.h"

bool MTTask::m_flag[3] = { { true },{ true },{ true }, };

#define IDLE_COUNT_LIMIT 10000000

//-------------------------------------------------------------------------------------------------
MTTask::MTTask(const std::string& sRootDir, IHash::HashType hashType , const std::string& dbname)
	:m_root(sRootDir)
	,m_dbname(dbname)
	,m_hashType(hashType)
	,m_qIn(0)
	,m_qMd5(0)
	,m_in(0)
	,m_gen(0)
	,m_out(0)
{

}

//-------------------------------------------------------------------------------------------------
MTTask::~MTTask()
{

}

//-------------------------------------------------------------------------------------------------
void MTTask::walkRoot(const std::string& root, QueueT* Queue)
{
	using namespace boost::filesystem;

	recursive_directory_iterator dir(root), end;

	while (m_flag[0])
	{
		while (dir != end)
		{
			const std::string sPath = dir->path().string();
			if (!sPath.empty())
			{
				HashData *pData = new HashData;
				pData->filename = sPath;
				Queue->push(pData);
			}
			dir++;
		}
	}
	m_flag[1] = false;
}

//-------------------------------------------------------------------------------------------------
void MTTask::md5Calc(QueueT* Queue, QueueT* pMd5Queue, IHash::HashType hashType)
{
	while (m_flag[1])
	{
		while ( !Queue->empty() )
		{
			HashData *pInData = 0;

			Queue->pop(pInData);
			try
			{
				if (!pInData->filename.empty())
				{
					unsigned long long fdatalen = FileSize(pInData->filename);

					if (!fdatalen)
						continue;

					HashData *pOutElem = new HashData;
					pOutElem->filename = pInData->filename;
					::time(&pOutElem->time);

					boost::shared_array<char> FileData;

					if (!GetFileData(pOutElem->filename, FileData, fdatalen))
					{
						delete pOutElem;
						continue;
					}

					boost::shared_ptr< IHash > pHash( IHash::create(hashType) );
					pHash->init();
					pHash->update(FileData, fdatalen);
					pHash->finalize();

					pOutElem->data = pHash->string();

					pMd5Queue->push(pOutElem);
					delete pInData;
				}
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}
	m_flag[2] = false;
}

//-------------------------------------------------------------------------------------------------
void MTTask::writeDb(QueueT* pMd5Queue)
{
	unsigned long long idle_cnt = 0;
	while (m_flag[2])
	{
		while (!pMd5Queue->empty())
		{
			idle_cnt = 0;
			HashData *pData = NULL;
			pMd5Queue->pop(pData);
			std::cout << "Filename: " << pData->filename << " Hash: " << pData->data << "\r\n";
			delete pData;
			continue;
		}
		++idle_cnt;
		if (idle_cnt > IDLE_COUNT_LIMIT)
			m_flag[0] = false;
		//std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

//-------------------------------------------------------------------------------------------------
bool MTTask::startInputThread()
{
	m_in.reset( new std::thread(&MTTask::walkRoot, m_root, &m_qIn) );
	return m_in.get() != NULL;
}

//-------------------------------------------------------------------------------------------------
bool MTTask::startGenerateThread()
{
	m_gen.reset( new std::thread(&MTTask::md5Calc, &m_qIn, &m_qMd5, m_hashType) );
	return m_gen.get() != NULL;
}

//-------------------------------------------------------------------------------------------------
bool MTTask::startOutputThread()
{
	m_out.reset( new std::thread( &MTTask::writeDb, &m_qMd5 ) );
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
