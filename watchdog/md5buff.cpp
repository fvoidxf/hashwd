/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#include "stdafx.h"

//=========================================================================
std::string __stdcall md5_buff(boost::shared_array<unsigned char>& data, size_t size)
{
	std::string md5str;
	std::stringstream md5ss;

	boost::shared_array<unsigned char> _MD5(new unsigned char[16]);

	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, data.get(), size);
	MD5_Final(_MD5.get(),&ctx);

	for(int i = 0; i < 16; i++)
	{
		md5ss << std::hex << std::setfill('0') <<  std::setw(2) << (int)_MD5[i];
	}

	md5str = md5ss.str();

	return md5str;
}


//=========================================================================
