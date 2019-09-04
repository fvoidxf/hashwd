#include "stdafx.h"
#include "mttask.h"

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
	while(!pInQueue->empty())
	{
		char *pName = 0;
		pInQueue->pop(pName);
		try
		{
			if(pName)
			{
				std::streampos fdatalen = filesize(pName);
				if(!fdatalen)
					continue;
				MidVal* pMid = new MidVal;
				pMid->fname = pName;
				::time(&pMid->time);
				pMid->md5 = new unsigned char[16];

				char *fdata = new char[fdatalen];

				std::ifstream _in(pName, std::ios::binary);
				while(!_in.eof()){
					_in.read(fdata,fdatalen);
				}
				_in.close();

				unsigned char *md5raw = new unsigned char[16];

				MD5_CTX ctx;
				MD5_Init(&ctx);
				MD5_Update(&ctx, fdata, fdatalen);
				MD5_Final(md5raw,&ctx);

				std::stringstream ss;

				for(int i = 0; i < 16; i++)
				{
					ss << std::hex << std::setfill('0') << std::setw(2) << (int)md5raw[i];
				}

				strcpy((char*)pMid->md5, ss.str().c_str());

				pMd5Queue->push(pMid);
				delete fdata;
			}
		}catch(std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

//-------------------------------------------------------------------------------------------------
std::streampos MTTask::filesize(const std::string& fname)
{
	std::streampos fsize = 0;
	std::ifstream file(fname, std::ios::binary);
	fsize = file.tellg();
	file.seekg( 0, std::ios::end );
	fsize = file.tellg() - fsize;
	file.close();
	return fsize;
}

//-------------------------------------------------------------------------------------------------
void MTTask::writeDb( boost::lockfree::queue<MidVal*, boost::lockfree::fixed_sized<false> >* pMd5Queue)
{
	while(!pMd5Queue->empty())
	{
		MidVal *pVal = 0;
		pMd5Queue->pop(pVal);
		std::cout << "Filename: " << pVal->fname << " MD5: " << pVal->md5 << "\r\n";
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(150));
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
}

//-------------------------------------------------------------------------------------------------
void MTTask::GenerateThreadJoin()
{
	m_gen->join();
}

//-------------------------------------------------------------------------------------------------
void MTTask::OutputThreadJoin()
{
	m_out->join();
}

//-------------------------------------------------------------------------------------------------
