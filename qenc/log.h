/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#ifndef __LOG_H__
#define __LOG_H__

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <string>

//=================================================================================================
class Log
{
public:
    enum Device
    {
      DevUnk = 0,
      DevConsole,
      DevFile,
    };

    enum Type
    {
        Unknown,
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    };

    Log(const std::string& Name, Device TDev = DevConsole, Type TType = Debug);
    virtual ~Log();

protected:
    Device      m_dev;
    Type        m_type;
    std::string m_devName;
    boost::log::sources::severity_logger< boost::log::trivial::severity_level > m_lg;

public:
    virtual bool init();
    virtual void write(const std::string& msg);
};

//=================================================================================================

#endif // __LOG_H__
