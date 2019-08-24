/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "log.h"

namespace kw = boost::log::keywords;

//-------------------------------------------------------------------------------------------------
Log::Log(const std::string& Name, Device TDev, Type TType)
    :m_devName(Name)
    ,m_dev(TDev)
    ,m_type(TType)
{

}

//-------------------------------------------------------------------------------------------------
Log::~Log()
{

}

//-------------------------------------------------------------------------------------------------
bool Log::init()
{
    if(m_dev == DevFile)
    {
        boost::log::add_file_log
        (
           kw::file_name = m_devName,
           kw::rotation_size = 10*1024,
           kw::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0,0,0),
           kw::format = "[%TimeStamp%]: %Message%"
        );

        boost::log::core::get()->set_filter
        (
           boost::log::trivial::severity >= boost::log::trivial::info
        );
        boost::log::add_common_attributes();
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------
void Log::write(const std::string& msg)
{
    BOOST_LOG_SEV(m_lg, boost::log::trivial::debug) << msg;
}

//-------------------------------------------------------------------------------------------------
