/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/

#include "stdafx.h"
#include "hash.h"
#include "db.h"
#include "filedata.h"
#include "filecontainer.h"
#include "mttask.h"

#define CTRL_FILE "sec.wd"

void usage(char *program)
{
	std::cout << "usage: " << program << "[-vph] -c md5 -s SESSION_NAME -d DIRECTORY" << std::endl;
	std::cout << "example: " << program << " -s Session1 -d C:\\temp" << std::endl;
	std::cout << "options: -v verbose output, -h help, -p parallel Execution" << std::endl;
	std::cout << "-c hash alghorytm, available md5, sha256, sha384, sha512" << std::endl;
}

int main(int argc, char *argv[])
{
	bool bIsExistsSession = false;
	bool isVerbose = false;
	bool bHelpOutput = false;
	bool isParallel = false;

	char *session = NULL;
	char *directory = NULL;
	char *hashing = NULL;

	IHash::HashType hashType = IHash::Undef;

	if(argc == 1)
	{
		usage(argv[0]);
		return 0;
	}

	char *options="c:s:d:vhp";
	int opt = 0;
	while((opt = getopt(argc, argv, options)) != -1)
	{
		switch(opt)
		{
		case 'v':
			isVerbose = true;
			break;
		case 'h':
			bHelpOutput = true;
			break;
		case 's':
			session = optarg;
			break;
		case 'd':
			directory = optarg;
			break;
		case 'p':
			isParallel = true;
			break;
		case 'c':
			hashing = optarg;
			break;
		}
	}

	if(bHelpOutput)
	{
		usage(argv[0]);
		return 0;
	}

	if(!session)
	{
		std::cerr << "Error: session name is not set!\r\n";
		return 0;
	}

	if(!directory)
	{
		std::cerr << "Error: directory name is not set!\r\n";
		return 0;
	}

	if (!hashing)
	{
		std::cerr << "Error: hashing alghorytm is not set!\r\n";
		return 0;
	}

	hashType = IHash::typeFromStr(hashing);
	if (hashType == IHash::Undef)
	{
		std::cerr << "Error: unknown hashing alghorytm!\r\n";
		return 0;
	}

	boost::filesystem::path targetDir(directory);

	if(!boost::filesystem::is_directory(targetDir))
	{
		std::cout << "The " << directory << " is not directory!\r\n";
		return 0;
	}

	if(!boost::filesystem::exists(targetDir))
	{
		std::cout << "The " << directory << " path does not exists!\r\n";
		return 0;
	}

	try
	{
		boost::shared_ptr<IFDContainer> strg(new FDContainer(session));

		if(!strg->connect())
		{
			std::cerr << "Can not open database.Exiting.\r\n";
			return 0;
		}

		bIsExistsSession = strg->isSessionExists();

		strg->setRoot(directory);

		if(isParallel)
		{
			MTTask task(directory, hashType);

			task.startInputThread();
			//task.InputThreadJoin();

			task.startGenerateThread();
			//task.GenerateThreadJoin();

			task.startOutputThread();
			//task.OutputThreadJoin();

			task.InputThreadJoin();		
			task.GenerateThreadJoin();
			task.OutputThreadJoin();

			return 0;
		}

		if(bIsExistsSession)
		{
			std::list<IFDContainer::DIFFS> diffList;

			strg->loadSession();
			if(isVerbose)
				strg->show();
			strg->diff(diffList);

			std::cout << "===================>     Founded changes:       <===================" << std::endl;

			for (IFDContainer::DIFFS df : diffList)
			{
				std::cout << "Found dif: " << df.filename << " old md5: " << df.wasMD5 << " now md5: " << df.nowMD5 << std::endl;
			}

			if(diffList.empty())
				std::cout << "No changes founded" << std::endl;
		}
		else
		{
			strg->create_session();
			strg->walk();
			strg->check_files();
			if(isVerbose)
				strg->show();
			strg->saveSession();
			strg->close();
		}

	}
	catch(std::exception& e)
	{
		std::cout << "Exception occurred:" << e.what();
		return 0;
	}
	catch(...)
	{
		std::cerr << "Undefined exception occurred!\r\n";
		return -1;
	}

	return 0;
}
