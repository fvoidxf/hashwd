#include "stdafx.h"
#include "db.h"
#include "filedata.h"
#include "filecontainer.h"

//-------------------------------------------------------------------------------------------------
FDContainer::~FDContainer()
{

}

//-------------------------------------------------------------------------------------------------
FDContainer::FDContainer(const std::string &session, const std::string& dbname )
	:m_db(session, dbname)
{

}

//-------------------------------------------------------------------------------------------------
void FDContainer::setRoot(const std::string& rootDir)
{
	m_root = rootDir;
}

//-------------------------------------------------------------------------------------------------
bool FDContainer::walk()
{
	if(m_root.empty())
		return false;
	return m_r_walk(m_root);
}

//-------------------------------------------------------------------------------------------------
bool FDContainer::m_r_walk(const boost::filesystem::path &loc)
{
	using namespace boost::filesystem;

	recursive_directory_iterator dir(loc), end;

	while(dir != end)
	{
		add(dir->path().string());
		dir++;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void FDContainer::add(const std::string& fileName, time_t *_t /*= NULL*/, const std::string& md5 /*= ""*/)
{
	boost::shared_ptr<IFileData> fd(new FileData(fileName, _t, md5));
	m_list.push_back(fd);
}

//-------------------------------------------------------------------------------------------------
void FDContainer::show()
{
	for(boost::shared_ptr<IFileData> fd : m_list)
	{
		std::cout << fd->fullname() << " HASH: " << fd->hash()  << std::endl;
	}
}

//-------------------------------------------------------------------------------------------------
void FDContainer::check_files()
{
	for(boost::shared_ptr<IFileData> fd : m_list)
	{
		if (!boost::filesystem::is_directory(fd->fullname()))
		{
			try
			{
					fd->make_hash();
			}
			catch(std::exception &e)
			{
				std::cerr << "Exception occurred while handling file: " << fd->fullname() << std::endl;
				std::cerr << e.what() << std::endl;
			}
			fd->setCurrentTime();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/*void FDContainer::setMaster(const std::string& masterFile)
{
	m_master = masterFile;
}*/

//-------------------------------------------------------------------------------------------------
/*bool FDContainer::haveCheckPoint()const
{
	std::string fullPath = m_root;
	fullPath += "\\";
	fullPath += m_master;

	return boost::filesystem::exists(fullPath);
}*/

//-------------------------------------------------------------------------------------------------
//void FDContainer::saveMaster()
//{
	/*std::string fullPath = m_root;
	fullPath += "\\";
	fullPath += m_master;

	std::ofstream ofs(fullPath);

	ofs << m_list.size();
	ofs << "\n";
	for (boost::shared_ptr<IFileData> fd : m_list)
	{
		ofs << fd->fullname();
		ofs << "::";
		ofs << fd->md5();
		ofs << "\n";
	}
	ofs.close();*/
//}
//-------------------------------------------------------------------------------------------------

//void FDContainer::loadMaster()
//{
/*	std::string fullPath = m_root;
	fullPath += "\\";
	fullPath += m_master;

	std::ifstream ifs(fullPath);

	size_t lstSize = 0;
	ifs >> lstSize;

	for (int i = 0; i < lstSize; i++)
	{
		std::string cmmn, fname, md5;
		ifs >> cmmn;
		int iPos = cmmn.find("::");
		if (iPos < 0)
			fname = cmmn;
		else
		{
			fname = cmmn.substr(0, iPos);
			md5 = cmmn.substr(iPos + 2);
		}
		add(fname, md5);
	}
	ifs.close();*/
//}

//-------------------------------------------------------------------------------------------------
void FDContainer::diff(std::list<DIFFS>& diffList)
{
	boost::shared_ptr<FDContainer> newCnt(new FDContainer(m_db.m_session));

	newCnt->setRoot(m_root);
	//newCnt->setMaster(m_master);
	newCnt->walk();
	newCnt->check_files();

	for (boost::shared_ptr<IFileData> fd : newCnt->m_list)
	{
		for (boost::shared_ptr<IFileData> fdd : m_list)
		{
			if (fd->fullname() == fdd->fullname())
			{
				if (fd->hash() != fdd->hash())
				{
					DIFFS dss;
					dss.filename = fd->fullname();
					dss.wasMD5 = fdd->hash();
					dss.nowMD5 = fd->hash();
					diffList.push_back(dss);
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool FDContainer::connect()
{
	return m_db.open();
}

//-------------------------------------------------------------------------------------------------
bool FDContainer::isSessionExists()
{
	return m_db.isSessionExists();
}

//-------------------------------------------------------------------------------------------------
void FDContainer::close()
{
	m_db.close();
}

//-------------------------------------------------------------------------------------------------
bool FDContainer::create_session()
{
	return m_db.create_session();
}

//-------------------------------------------------------------------------------------------------
void FDContainer::saveSession()
{
	for (boost::shared_ptr<IFileData> fd : m_list)
	{
		m_db.addData(fd->fullname(), fd->time(), fd->hash());
	}
}

//-------------------------------------------------------------------------------------------------
void FDContainer::loadSession()
{
	m_db.load_session(this);
}

//-------------------------------------------------------------------------------------------------
