/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#pragma once

bool GetFileData(const std::string& filename, boost::shared_array<char>& data, unsigned long long filesize);
