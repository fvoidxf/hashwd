/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include "config.h"
#include "dynmodel.h"
#include "control.h"
#include "fieldthread.h"

//-------------------------------------------------------------------------------------------------
Control::Control()
	:m_model( new DynModel( Config::instance()->columns(), Config::instance()->rows() ) )
	,m_thread( new FieldThread )
{

}

//-------------------------------------------------------------------------------------------------
Control::~Control()
{
	if (m_model)
		delete m_model;
	if (m_thread)
	{
		if (m_thread->isRunning())
		{
			m_thread->setStopFlag();
			m_thread->wait(Config::instance()->threadTerminateTimeoutMs());
			m_thread->terminate();
			delete m_thread;
		}
	}
}

//-------------------------------------------------------------------------------------------------
